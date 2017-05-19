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
        private Boolean _playingMusic = false;
        private int _round = 0;
        private int _totalScore = 0;
        private ObservableCollection<StorageFile> AllSongs;
        private ObservableCollection<Song> Songs;

        public Home()
        {
            this.InitializeComponent();

            ((ViewModel.MusicGameViewModel)DataContext).InitialViewModel();

            Messenger.Default.Register<string>(
                this,
                "play",
                HandlePLayMessage);

            Messenger.Default.Register<string>(
                this,
                "stop",
                HandleStopMessage);

            // Songs = new ObservableCollection<Song>();
        }

        private void HandlePLayMessage(string obj)
        {
            MyMediaElement.Play();
        }

        private void HandleStopMessage(string obj)
        {
            MyMediaElement.Stop();
        }

        private void ClickCheck_Click(object sender, RoutedEventArgs e)
        {
            ButtonText.Text = (Int32.Parse(ButtonText.Text) + 1).ToString();
        }
    }
}
