using GalaSoft.MvvmLight.Messaging;
using MusicGame.Models;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Threading.Tasks;
using Windows.Storage;
using Windows.Storage.FileProperties;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Imaging;

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

            Messenger.Default.Register<StorageFile>(
                this,
                "play",
                HandlePLayMessage);

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
                    }
                });

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
        }

        private void HandleStopMessage(StorageFile myStorageFile)
        {
            //var fileStream = await myStorageFile.OpenAsync(FileAccessMode.Read);
            //MyMediaElement.SetSource(fileStream, myStorageFile.ContentType);
            MyMediaElement.Stop();
        }

        private void ClickCheck_Click(object sender, RoutedEventArgs e)
        {
            ButtonText.Text = (Int32.Parse(ButtonText.Text) + 1).ToString();
        }

        private void ShortCountDown_Completed(object sender, object e)
        {
            ((ViewModel.MusicGameViewModel)DataContext).CountDown_Completed();
        }

        private void SongGridView_ItemClick(object sender, ItemClickEventArgs e)
        {
            ((ViewModel.MusicGameViewModel)DataContext).SongGridView_ItemClick(sender, e);
        }
    }
}
