using GalaSoft.MvvmLight.Messaging;
using System;
using Windows.Storage;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;

// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

namespace MusicGame.Views
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class Home : Page
    {
        public Home()
        {
            this.InitializeComponent();
            MoePicture_Yande.Styles.Win2D.initialGlass(background);

            Messenger.Default.Register<string>(
                this,
                "count",
                (str) =>
                {
                    switch (str)
                    {
                        case "short":
                            ShortCountDown.Begin();
                            break;

                        case "normal":
                            CountDown.Begin();
                            break;

                        case "stopAll":
                            CountDown.Stop();
                            ShortCountDown.Stop();
                            break;
                    }
                });

            Messenger.Default.Register<StorageFile>(
               this,
               "play",
               HandlePLayMessage);

            Messenger.Default.Register<StorageFile>(
                this,
                "stop",
                HandleStopMessage);
        }

        private async void HandlePLayMessage(StorageFile myStorageFile)
        {
            var fileStream = await myStorageFile.OpenAsync(FileAccessMode.Read);
            MyMediaElement.SetSource(fileStream, myStorageFile.ContentType);
            MyMediaElement.Play();
            ((ViewModel.MusicGameViewModel)DataContext).IsPlaying = true;
        }

        private void HandleStopMessage(StorageFile myStorageFile)
        {
            MyMediaElement.Stop();
            ((ViewModel.MusicGameViewModel)DataContext).IsPlaying = false;
        }

        private void SongGridView_ItemClick(object sender, ItemClickEventArgs e)
        {
            ((ViewModel.MusicGameViewModel)DataContext).SongGridView_ItemClick(sender, e);
        }

        protected override void OnNavigatingFrom(NavigatingCancelEventArgs e)
        {
            MyMediaElement.Stop();
            ShortCountDown.Stop();
            CountDown.Stop();
        }

        private void CountDown_Completed(object sender, object e)
        {
            ((ViewModel.MusicGameViewModel)DataContext).CountDown_Completed();
        }

        private void ShortCountDown_Completed(object sender, object e)
        {
            ((ViewModel.MusicGameViewModel)DataContext).ShortCountDown_Completed();
        }
    }
}
