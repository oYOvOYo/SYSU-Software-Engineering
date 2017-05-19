using System;
using Windows.Storage;
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
        public Boolean Selected { get; set; }
        public BitmapImage AlbumCover { get; set; }
        public Boolean Used { get; set; }
    }
}
