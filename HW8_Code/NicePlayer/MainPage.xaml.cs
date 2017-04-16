using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Media.Core;
using Windows.UI.ViewManagement;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x804 上介绍了“空白页”项模板

namespace NicePlayer
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            mediaElement.CurrentStateChanged += MediaElement_CurrentStateChanged;
            mediaElement.MediaOpened += MediaElement_MediaOpened;
        }

        private void MediaElement_MediaOpened(object sender, RoutedEventArgs e)
        {
            positionSlider.Value = 0;
        }

        private void MediaElement_CurrentStateChanged(object sender, RoutedEventArgs e)
        {
            switch ((sender as Windows.UI.Xaml.Controls.MediaElement).CurrentState)
            {
                case MediaElementState.Playing:
                    Rotate.Begin();
                    break;
                case MediaElementState.Paused:
                    Rotate.Pause();
                    break;
                default:
                    Rotate.Stop();
                    break;
            }
        }

        private async void File_Click(object sender, RoutedEventArgs e)
        {
            var picker = new Windows.Storage.Pickers.FileOpenPicker();
            picker.ViewMode = Windows.Storage.Pickers.PickerViewMode.Thumbnail;
            picker.SuggestedStartLocation =
                Windows.Storage.Pickers.PickerLocationId.VideosLibrary;
            picker.FileTypeFilter.Add(".mp4");
            picker.FileTypeFilter.Add(".mkv");
            picker.FileTypeFilter.Add(".mp3");

            Windows.Storage.StorageFile file = await picker.PickSingleFileAsync();
            if (file != null)
            {
                // Application now has read/write access to the picked file
                try
                {
                    var stream = await file.OpenAsync(Windows.Storage.FileAccessMode.Read);
                    mediaElement.SetSource(stream, file.ContentType);
                    mediaElement.Play();
                }
                catch
                {
                    // fail to open 
                }
                
            }
        }

        private void FullScreen_Click(object sender, RoutedEventArgs e)
        {
            if (mediaElement.Stretch != Stretch.Fill)
            {
                mediaElement.Stretch = Stretch.Fill;
                ((sender as Button).Content as SymbolIcon).Symbol = Symbol.BackToWindow;
            } else
            {
                mediaElement.Stretch = Stretch.Uniform;
                ((sender as Button).Content as SymbolIcon).Symbol = Symbol.FullScreen;
            }
        }

        private void Play_Click(object sender, RoutedEventArgs e)
        {
            mediaElement.Play();
        }

        private void Pause_Click(object sender, RoutedEventArgs e)
        {
            mediaElement.Pause();
        }

        private void Stop_Click(object sender, RoutedEventArgs e)
        {
            mediaElement.Stop();
        }

        private void Grid_PointerEntered(object sender, PointerRoutedEventArgs e)
        {
            ControlPanel.Height = 48;
        }

        private void Grid_PointerExited(object sender, PointerRoutedEventArgs e)
        {
            ControlPanel.Height = 0;
        }

        private void Volume_Click(object sender, RoutedEventArgs e)
        {
            VolumeSlider.Opacity = VolumeSlider.Opacity == 0 ? 1.0 : 0;
        }

        private void mediaElement_MediaOpened(object sender, RoutedEventArgs e)
        {
            if (mediaElement.IsAudioOnly)
            {

            }
        }
    }

}
