using GalaSoft.MvvmLight;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Storage;
using MusicGame.Models;
using Microsoft.Practices.ServiceLocation;
using Windows.Storage.FileProperties;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using GalaSoft.MvvmLight.Messaging;
using GalaSoft.MvvmLight.Command;
using System.Threading;

namespace MusicGame.ViewModel
{
    public class MusicGameViewModel : ViewModelBase
    {
        private bool _isLoding;
        private bool _isPlaying;
        private int _totalScore;
        private int _round;
        private string _instruction;
        private string _result;
        private Visibility _playAgainButton;
        private UserConfig _config;
        private List<StorageFile> _songFiles;
        private ObservableCollection<Song> _songs;
        private Song _selectSong;
        private FilesServer _filesServer;

        public bool IsLoding { get => _isLoding; set { _isLoding = value; RaisePropertyChanged(() => IsLoding); } }
        public string Instruction { get => _instruction; set { _instruction = value; RaisePropertyChanged(() => Instruction); } }
        public string Result { get => _result; set { _result = value; RaisePropertyChanged(() => Result); } }
        public Visibility PlayAgainButton { get => _playAgainButton; set { _playAgainButton = value; RaisePropertyChanged(() => PlayAgainButton); } }

        public bool IsPlaying { get => _isPlaying; set => _isPlaying = value; }
        public int TotalScore { get => _totalScore; set => _totalScore = value; }
        public int Round { get => _round; set => _round = value; }
        public UserConfig Config { get => _config; set => _config = value; }
        public List<StorageFile> SongFiles { get => _songFiles; set => _songFiles = value; }
        public ObservableCollection<Song> Songs { get => _songs; set { _songs = value; RaisePropertyChanged(() => Songs); } }
        public Song SelectSong { get => _selectSong; set { _selectSong = value; } }

        public MusicGameViewModel(FilesServer filesServer)
        {
            _filesServer = filesServer;
        }

        public async Task InitialViewModel()
        {
            IsLoding = true;

            IsPlaying = false;
            TotalScore = 0;
            Round = 0;
            Instruction = "";
            Result = "";
            PlayAgainButton = Visibility.Collapsed;
            Config = ServiceLocator.Current.GetInstance<UserConfigViewModel>().UserConfig;
            SongFiles = await _filesServer.GetAllFiles(Config.FolderPath, ".mp3");
            Songs = new ObservableCollection<Song>();
            SelectSong = new Song();

            IsLoding = false;
        }

        private RelayCommand _gridLoadCommand;

        public RelayCommand GridLoadCommand
        {
            get
            {
                return _gridLoadCommand ??
                    (_gridLoadCommand = new RelayCommand(
                    async () =>
                    {
                        IsLoding = true;
                        await InitialViewModel();
                        await PrepareNewGame();
                        IsLoding = false;
                    }));
            }
        }

        private async Task PrepareNewGame()
        {
            IsLoding = true;
            IsPlaying = false;
            TotalScore = 0;
            Round = 0;
            Instruction = "Get Ready :)";
            Result = "";
            Songs.Clear();
            SelectSong = new Song();
            RaisePropertyChanged(() => SelectSong);

            // Choose random songs from library.
            // Pluck off meta data from selected songs.
            await PopulateSongList(await PickRandomSongs(SongFiles, Config.EachRoundChoicesNumber));

            IsLoding = false;
            StartShortCountdown();
        }

        private static SemaphoreSlim ClickLock = new SemaphoreSlim(1);

        public async void SongGridView_ItemClick(object sender, ItemClickEventArgs e)
        {
            if (!IsPlaying || Round >= Config.RoundNumber) return;

            await ClickLock.WaitAsync();

            Song clickedSong = (Song)e.ClickedItem;
            EndRound(clickedSong);

            Uri uri = clickedSong == SelectSong ? UserConfig.WinImageUri : UserConfig.LoseImageUri;
            StorageFile file = await StorageFile.GetFileFromApplicationUriAsync(uri);
            var fileStream = await file.OpenAsync(FileAccessMode.Read);
            await clickedSong.AlbumCover.SetSourceAsync(fileStream);
            clickedSong.Used = true;

            ClickLock.Release();
        }

        public void CountDown_Completed()
        {
            EndRound(null);
        }

        public void ShortCountDown_Completed()
        {
            StartCountdown();
        }

        private void EndRound(Song song)
        {
            Messenger.Default.Send(SelectSong.SongFile, "stop");
            DisplayCorrectSong();
            int score = SelectSong == song ? UserConfig.WinScore : UserConfig.LoseScore;
            TotalScore += score;
            Result = String.Format("Score: {0}, Total Score after {1} Rounds: {2}", score, Round + 1, TotalScore);
            Round++;

            if (Round == Config.RoundNumber)
            {
                Messenger.Default.Send("stopAll", "count");
                Instruction = String.Format("Game Over... You scored: {0}", TotalScore);
                PlayAgainButton = Visibility.Visible;
            }
            else
            {
                StartShortCountdown();
            }
        }

        private void StartShortCountdown()
        {
            if (Round < Config.RoundNumber)
            {
                Instruction = String.Format("Get ready for The Round {0}", Round + 1);
                Messenger.Default.Send("short", "count");
            }
        }

        private void StartCountdown()
        {
            SelectSong = PickSong();
            Messenger.Default.Send(SelectSong.SongFile, "play");
            Instruction = "Playing Music...♪";
            Messenger.Default.Send("normal", "count");
        }

        private RelayCommand _playAgainCommand;

        public RelayCommand PlayAgainCommand
        {
            get
            {
                return _playAgainCommand
                       ?? (_playAgainCommand = new RelayCommand(
                           async () =>
                           {
                               PlayAgainButton = Visibility.Collapsed;
                               await PrepareNewGame();
                           }));
            }
        }

        private void DisplayCorrectSong()
        {
            RaisePropertyChanged(() => SelectSong);
        }

        private async Task<List<StorageFile>> PickRandomSongs(List<StorageFile> allSongs, int pickNumber)
        {
            Random random = new Random();
            int songCount = allSongs.Count;
            var randomSongs = new List<StorageFile>();

            while (randomSongs.Count < pickNumber)
            {
                var randomNumber = random.Next(songCount);
                var randomSong = allSongs[randomNumber];

                MusicProperties randomSongMusicProperties =
                                    await randomSong.Properties.GetMusicPropertiesAsync();

                bool isDuplicate = false;
                foreach (var song in randomSongs)
                {
                    MusicProperties songMusicProperties =
                        await song.Properties.GetMusicPropertiesAsync();

                    // Find random songs But:
                    // (1) Don't pick the same song twice.
                    // (2) Don't pick a song from an album that I've already picked.

                    if (String.IsNullOrEmpty(randomSongMusicProperties.Album)
                        || randomSongMusicProperties.Album == songMusicProperties.Album)
                    {
                        isDuplicate = true;
                    }
                }
                if (!isDuplicate)
                {
                    randomSongs.Add(randomSong);
                }
            }
            return randomSongs;
        }

        private Song PickSong()
        {
            Random random = new Random();
            var unusedSongs = Songs.Where(p => !p.Used);
            var randomNumber = random.Next(unusedSongs.Count());
            var randomSong = unusedSongs.ElementAt(randomNumber);
            return randomSong;
        }

        private async Task PopulateSongList(List<StorageFile> files)
        {
            int id = 0;

            foreach (var file in files)
            {
                Song song = await Song.CreateSong(file);
                song.Id = id;
                Songs.Add(song);
                id++;
            }
        }
    }
}
