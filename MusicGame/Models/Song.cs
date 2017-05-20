using System;
using System.Threading.Tasks;
using Windows.Storage;
using Windows.Storage.FileProperties;
using Windows.UI.Xaml.Media.Imaging;

namespace MusicGame.Models
{
    public class Song
    {
        public int Id { get; set; }
        public String Title { get; set; }
        public String Artist { get; set; }
        public String Album { get; set; }
        public StorageFile SongFile { get; set; }
        public BitmapImage AlbumCover { get; set; }
        public Boolean Used { get; set; }

        public static async Task<Song> CreateSong(StorageFile file)
        {
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
            song.Used = false;
            song.AlbumCover = albumCover;
            song.SongFile = file;
            return song;
        }
    }
}
