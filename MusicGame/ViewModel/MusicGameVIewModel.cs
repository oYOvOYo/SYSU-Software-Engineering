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

        public Uri MediaUri
        {
            get => SelectSong.SongFile != null ? new Uri(SelectSong.SongFile.Path) : null;
        }

        public bool IsLoding
        {
            get => _isLoding; set
            {
                _isLoding = value;
                RaisePropertyChanged(() => IsLoding);
            }
        }

        public bool IsPlaying { get => _isPlaying; set => _isPlaying = value; }

        public string Instruction
        {
            get => _instruction;
            set { _instruction = value; RaisePropertyChanged(() => Instruction); }
        }

        public string Result
        {
            get => _result; set
            {
                _result = value;
                RaisePropertyChanged(() => Result);
            }
        }

        public Visibility PlayAgainButton
        {
            get => _playAgainButton;
            set { _playAgainButton = value; RaisePropertyChanged(() => PlayAgainButton); }
        }

        public int TotalScore { get => _totalScore; set => _totalScore = value; }
        public int Round { get => _round; set => _round = value; }
        public UserConfig Config { get => _config; set => _config = value; }
        public List<StorageFile> SongFiles { get => _songFiles; set => _songFiles = value; }
        public ObservableCollection<Song> Songs { get => _songs; set => _songs = value; }
        public Song SelectSong { get => _selectSong; set { _selectSong = value; RaisePropertyChanged(() => MediaUri); } }

        public MusicGameViewModel(FilesServer filesServer)
        {
            _filesServer = filesServer;
            Songs = new ObservableCollection<Song>();
            SelectSong = new Song();
        }

        public async Task InitialViewModel()
        {
            IsLoding = true;
            PlayAgainButton = Visibility.Collapsed;
            Instruction = "";
            Result = "";
            Config = ServiceLocator.Current.GetInstance<UserConfigViewModel>().UserConfig;
            SongFiles = await _filesServer.GetAllFiles(Config.FolderPath, ".mp3");
            IsLoding = false;
        }

        private RelayCommand _countFinishedCommand;

        public RelayCommand CountFinishedCommand
        {
            get
            {
                return _countFinishedCommand ??
                    (_countFinishedCommand = new RelayCommand(
                        () =>
                        {
                            CountDown_Completed();
                        }));
            }
        }

        public void CountDown_Completed()
        {
            if (!IsPlaying)
            {
                // Start playing music
                SelectSong = PickSong();
                // Play the music
                Messenger.Default.Send(SelectSong.SongFile, "play");
                // Start countdown
                StartCountdown();
            }
            else
            {
                Messenger.Default.Send(SelectSong.SongFile, "stop");
                Song correctSong = Songs.FirstOrDefault(p => p.Selected);
                correctSong.Selected = false;
                correctSong.Used = true;
                DisplayCorrectSong(correctSong);
                int addScore = (-1) * 100;
                TotalScore += addScore;
                Round++;
                Result = String.Format("Score: {0}, Total Score after {1} Rounds: {2}", addScore, Round, TotalScore);
                if (_round >= 5)
                {
                    Instruction = String.Format("Game Over... You scored: {0}", _totalScore);
                    PlayAgainButton = Visibility.Visible;
                }
                else
                {
                    StartShortCountdown();
                }
            }
        }

        private void DisplayCorrectSong(Song correctSong)
        {
            RaisePropertyChanged(() => SelectSong);
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
                        StartShortCountdown();
                    }));
            }
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
            randomSong.Selected = true;
            return randomSong;
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
                               IsLoding = true;
                               await PrepareNewGame();
                               IsLoding = false;
                           }));
            }
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

        private async Task PrepareNewGame()
        {
            Songs.Clear();

            // State management
            Instruction = "Get Ready :)";
            _totalScore = 0;

            // Choose random songs from library.
            var randomSongFiles = await PickRandomSongs(SongFiles, 10);

            // Pluck off meta data from selected songs.
            await PopulateSongList(randomSongFiles);
            StartShortCountdown();
        }

        public async void SongGridView_ItemClick(object sender, ItemClickEventArgs e)
        {
            // Ignore clicks when we are in cooldown
            if (!IsPlaying)
            {
                return;
            }

            // CountDown.Pause();
            Messenger.Default.Send(SelectSong.SongFile, "stop");

            Song clickedSong = (Song)e.ClickedItem;
            Song correctSong = Songs.FirstOrDefault(p => p.Selected);

            // Evaluate the user's selection
            Uri uri = null;
            int addScore = 0;

            if (clickedSong.Selected)
            {
                uri = new Uri("ms-appx:///Assets/correct.png");
                addScore = 100;
            }
            else
            {
                uri = new Uri("ms-appx:///Assets/incorrect.png");
                addScore = (-1) * 100;
            }

            // Setting the picture.
            StorageFile file = await StorageFile.GetFileFromApplicationUriAsync(uri);
            var fileStream = await file.OpenAsync(FileAccessMode.Read);
            await clickedSong.AlbumCover.SetSourceAsync(fileStream);

            _totalScore += addScore;
            _round++;
            Result = String.Format("Score: {0}, Total Score after {1} Rounds: {2}", addScore, _round, _totalScore);
            DisplayCorrectSong(correctSong);

            clickedSong.Used = true;
            correctSong.Selected = false;
            correctSong.Used = true;

            if (_round >= 5)
            {
                Instruction = String.Format("Game Over... You scored: {0}", _totalScore);
                PlayAgainButton = Visibility.Visible;
            }
            else
            {
                StartShortCountdown();
            }
        }

        private void StartShortCountdown()
        {
            IsPlaying = false;
            Instruction = String.Format("Get ready for The Round {0}", Round + 1);
            Messenger.Default.Send("short", "count");
        }

        private void StartCountdown()
        {
            IsPlaying = true;
            Instruction = "Playing Music...♪";
            Messenger.Default.Send("normal", "count");
        }
    }
}
