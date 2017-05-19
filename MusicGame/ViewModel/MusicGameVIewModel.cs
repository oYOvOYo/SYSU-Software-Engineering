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

namespace MusicGame.ViewModel
{
    public class MusicGameViewModel : ViewModelBase
    {
        private bool _isLoding;
        private bool _isPlaying;
        private int _totalScore;
        private string _instruction;
        private UserConfig _config;
        private List<StorageFile> _songFiles;
        private ObservableCollection<Song> _songs;
        private Song _selectSong;
        private FilesServer _filesServer;

        public bool IsLoding { get => _isLoding; set { _isLoding = value; RaisePropertyChanged(() => IsLoding); } }
        public bool IsPlaying { get => _isPlaying; set => _isPlaying = value; }
        public string Instruction { get => _instruction; set => _instruction = value; }
        public int TotalScore { get => _totalScore; set => _totalScore = value; }
        public UserConfig Config { get => _config; set => _config = value; }
        public List<StorageFile> SongFiles { get => _songFiles; set => _songFiles = value; }
        public ObservableCollection<Song> Songs { get => _songs; set => _songs = value; }
        public Song SelectSong { get => _selectSong; set { _selectSong = value; RaisePropertyChanged(() => SelectSong); } }

        public MusicGameViewModel(FilesServer filesServer)
        {
            _filesServer = filesServer;
        }

        public async void InitialViewModel()
        {
            IsLoding = true;
            Config = ServiceLocator.Current.GetInstance<UserConfigViewModel>().UserConfig;
            SongFiles = await _filesServer.GetAllFiles(Config.FolderPath, ".mp3");
            var file = SongFiles[0];

            MusicProperties songProperties = await file.Properties.GetMusicPropertiesAsync();
            StorageItemThumbnail currentThumb = await file.GetThumbnailAsync(
                ThumbnailMode.MusicView,
                200,
                ThumbnailOptions.UseCurrentScale);

            var albumCover = new BitmapImage();
            albumCover.SetSource(currentThumb);

            var song = new Song();
            song.Id = 0;
            song.Title = songProperties.Title;
            song.Artist = songProperties.Artist;
            song.Album = songProperties.Album;
            song.Selected = false;
            song.Used = false;
            song.AlbumCover = albumCover;
            song.SongFile = file;
            SelectSong = song;

            IsLoding = false;
        }

        //private async void CountDown_Completed(object sender, object e)
        //{
        //    if (!IsPlaying)
        //    {
        //        // Start playing music
        //        var song = PickSong();

        //        // Play the music
        //        MyMediaElement.SetSource(
        //            await song.SongFile.OpenAsync(FileAccessMode.Read),
        //            song.SongFile.ContentType);

        //        // Start countdown
        //        StartCountdown();
        //    }
        //    else
        //    {
        //        MyMediaElement.Stop();
        //        Song correctSong = Songs.FirstOrDefault(p => p.Selected);
        //        correctSong.Selected = false;
        //        correctSong.Used = true;
        //        DisplayCorrectSong(correctSong);
        //        int addScore = (-1) * (int)MyProgressBar.Value;
        //        _totalScore += addScore;
        //        _round++;
        //        ResultTextBlock.Text = String.Format("Score: {0}, Total Score after {1} Rounds: {2}", addScore, _round, _totalScore);
        //        if (_round >= 5)
        //        {
        //            InstructionTextBlock.Text = String.Format("Game Over... You scored: {0}", _totalScore);
        //            PlayAgainButton.Visibility = Visibility.Visible;
        //        }
        //        else
        //        {
        //            StartCooldown();
        //        }
        //    }
        //}

        //private void DisplayCorrectSong(Song correctSong)
        //{
        //    TitleTextBlock.Text = String.Format("{0}", correctSong.Title);
        //    ArtistTextBlock.Text = String.Format("{0}", correctSong.Artist);
        //    AlbumTextBlock.Text = String.Format("{0}", correctSong.Album);
        //    ResultImage.Source = correctSong.AlbumCover;
        //}

        //private async void Grid_Loaded(object sender, RoutedEventArgs e)
        //{
        //    StartUpProgressRing.IsActive = true;

        //    AllSongs = await SetupMusicList();
        //    await PrepareNewGame();

        //    StartUpProgressRing.IsActive = false;

        //    StartCooldown();
        //}

        //private async Task<List<StorageFile>> PickRandomSongs(ObservableCollection<StorageFile> allSongs, int pickNumber)
        //{
        //    Random random = new Random();
        //    int songCount = allSongs.Count;
        //    var randomSongs = new List<StorageFile>();

        //    while (randomSongs.Count < pickNumber)
        //    {
        //        var randomNumber = random.Next(songCount);
        //        var randomSong = allSongs[randomNumber];

        //        MusicProperties randomSongMusicProperties =
        //                            await randomSong.Properties.GetMusicPropertiesAsync();

        //        bool isDuplicate = false;
        //        foreach (var song in randomSongs)
        //        {
        //            MusicProperties songMusicProperties =
        //                await song.Properties.GetMusicPropertiesAsync();

        //            // Find random songs But:
        //            // (1) Don't pick the same song twice.
        //            // (2) Don't pick a song from an album that I've already picked.

        //            if (String.IsNullOrEmpty(randomSongMusicProperties.Album)
        //                || randomSongMusicProperties.Album == songMusicProperties.Album)
        //            {
        //                isDuplicate = true;
        //            }
        //        }
        //        if (!isDuplicate)
        //        {
        //            randomSongs.Add(randomSong);
        //        }
        //    }
        //    return randomSongs;
        //}

        //private Song PickSong()
        //{
        //    Random random = new Random();
        //    var unusedSongs = Songs.Where(p => !p.Used);
        //    var randomNumber = random.Next(unusedSongs.Count());
        //    var randomSong = unusedSongs.ElementAt(randomNumber);
        //    randomSong.Selected = true;
        //    return randomSong;
        //}

        //private async void PlayAgainButton_Click(object sender, RoutedEventArgs e)
        //{
        //    PlayAgainButton.Visibility = Visibility.Collapsed;
        //    StartUpProgressRing.IsActive = true;
        //    await PrepareNewGame();
        //    StartUpProgressRing.IsActive = false;
        //}

        //private async Task PopulateSongList(List<StorageFile> files)
        //{
        //    int id = 0;

        //    foreach (var file in files)
        //    {
        //        MusicProperties songProperties = await file.Properties.GetMusicPropertiesAsync();

        //        StorageItemThumbnail currentThumb = await file.GetThumbnailAsync(
        //            ThumbnailMode.MusicView,
        //            200,
        //            ThumbnailOptions.UseCurrentScale);

        //        var albumCover = new BitmapImage();
        //        albumCover.SetSource(currentThumb);

        //        var song = new Song();
        //        song.Id = id;
        //        song.Title = songProperties.Title;
        //        song.Artist = songProperties.Artist;
        //        song.Album = songProperties.Album;
        //        song.Selected = false;
        //        song.Used = false;
        //        song.AlbumCover = albumCover;
        //        song.SongFile = file;

        //        Songs.Add(song);
        //        id++;
        //    }
        //}

        //private async Task PrepareNewGame()
        //{
        //    Songs.Clear();

        //    // State management
        //    InstructionTextBlock.Text = "Get Ready :)";
        //    ResultTextBlock.Text = "";
        //    TitleTextBlock.Text = "";
        //    ArtistTextBlock.Text = "";
        //    AlbumTextBlock.Text = "";
        //    ResultImage.Source = null;
        //    _totalScore = 0;
        //    _round = 0;

        //    // Choose random songs from library.
        //    var randomSongs = await PickRandomSongs(AllSongs, 10);

        //    // Pluck off meta data from selected songs.
        //    await PopulateSongList(randomSongs);
        //    StartCooldown();
        //}

        //private async void SongGridView_ItemClick(object sender, ItemClickEventArgs e)
        //{
        //    // Ignore clicks when we are in cooldown
        //    if (!_playingMusic)
        //    {
        //        return;
        //    }

        //    CountDown.Pause();
        //    MyMediaElement.Stop();

        //    Song clickedSong = (Song)e.ClickedItem;
        //    Song correctSong = Songs.FirstOrDefault(p => p.Selected);

        //    // Evaluate the user's selection
        //    Uri uri = null;
        //    int addScore = 0;

        //    if (clickedSong.Selected)
        //    {
        //        uri = new Uri("ms-appx:///Assets/correct.png");
        //        addScore = (int)MyProgressBar.Value;
        //    }
        //    else
        //    {
        //        uri = new Uri("ms-appx:///Assets/incorrect.png");
        //        addScore = (-1) * (int)MyProgressBar.Value;
        //    }

        //    // Setting the picture.
        //    StorageFile file = await StorageFile.GetFileFromApplicationUriAsync(uri);
        //    var fileStream = await file.OpenAsync(FileAccessMode.Read);
        //    await clickedSong.AlbumCover.SetSourceAsync(fileStream);

        //    _totalScore += addScore;
        //    _round++;
        //    ResultTextBlock.Text = String.Format("Score: {0}, Total Score after {1} Rounds: {2}", addScore, _round, _totalScore);
        //    DisplayCorrectSong(correctSong);

        //    clickedSong.Used = true;
        //    correctSong.Selected = false;
        //    correctSong.Used = true;

        //    if (_round >= 5)
        //    {
        //        InstructionTextBlock.Text = String.Format("Game Over... You scored: {0}", _totalScore);
        //        PlayAgainButton.Visibility = Visibility.Visible;
        //    }
        //    else
        //    {
        //        StartCooldown();
        //    }
        //}

        //private void StartCooldown()
        //{
        //    _playingMusic = false;
        //    InstructionTextBlock.Text = String.Format("Get ready for round {0}...", _round + 1);
        //    ShortCountDown.Begin();
        //}

        //private void StartCountdown()
        //{
        //    _playingMusic = true;
        //    InstructionTextBlock.Text = "Playing Music...♪";
        //    CountDown.Begin();
        //}
    }
}
