using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// WTF
using Windows.UI.Xaml.Media.Imaging;

// “空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=234238 上有介绍

namespace HomeWork1
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class Main : Page
    {
        // Player Request 
        enum UserRequest { NO_REQUEST, LET_ME_WIN, LET_ME_LOSE};
        // Store Your Request
        private UserRequest YouWant;
        // delegate and event
        private delegate void Game(object sender, AnimalName e);
        private Game GameStart;

        public Main()
        {
            this.InitializeComponent();
            // intial values
            YouWant = UserRequest.NO_REQUEST;
            GameStart += AnimalGame;
        }

        private void AnimalGame(object sender, AnimalName e)
        {
            InitialGame(sender, e);
            // get ans and update content
            string YourAns = e.Args;
            string RightAns = PickRandomAnimalName();

            if (YouWant == UserRequest.LET_ME_WIN)
            {
                while (RightAns != YourAns)
                {
                    RightAns = PickRandomAnimalName();
                }
            }

            if (YouWant == UserRequest.LET_ME_LOSE)
            {
                while (RightAns == YourAns)
                {
                    RightAns = PickRandomAnimalName();
                }
            }

            YouWant = UserRequest.NO_REQUEST;

            UpdateImg(sender, YourAns, RightAns);
            // show ans 
            if (YourAns == RightAns)
            {
                DispalyWinMessage(sender);
            } else
            {
                DisplatLoseMessage(sender);
            }
            
        }

        private void InitialGame(object sender, RoutedEventArgs e)
        {
            // Img
            YourImg.Opacity = 0;
            RightImg.Opacity = 0;
            // Ans
            WinText.Opacity = 0;
            WinImg.Opacity = 0;
            LoseText.Opacity = 0;
            LoseImg.Opacity = 0;
        }

        private void UpdateImg(object sender, string YourAns, string RightAns)
        {
            // rource and opacity
            string WhereIsImg = "ms-appx:/Assets/Img.png";
            YourImg.Source = new BitmapImage(new Uri(WhereIsImg.Replace("Img", YourAns), UriKind.RelativeOrAbsolute));
            RightImg.Source = new BitmapImage(new Uri(WhereIsImg.Replace("Img", RightAns), UriKind.RelativeOrAbsolute));
            YourImg.Opacity = 1;
            RightImg.Opacity = 1;
        }

        private void DispalyWinMessage(object sender)
        {
            WinText.Opacity = 1;
            WinImg.Opacity = 1;
        }

        private void DisplatLoseMessage(object sender)
        {
            LoseText.Opacity = 1;
            LoseImg.Opacity = 1;
        }


        private void CatButton_Click(object sender, RoutedEventArgs e)
        {
            GameStart(sender, new AnimalName("cat"));
        }

        private void DogButton_Click(object sender, RoutedEventArgs e)
        {
            GameStart(sender, new AnimalName("dog"));

        }

        private void PigButton_Click(object sender, RoutedEventArgs e)
        {
            GameStart(sender, new AnimalName("pig"));
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            // back to Mainpage
            this.Frame.Navigate(typeof(MainPage));
        }

        private void LetMeWin_Click(object sender, RoutedEventArgs e)
        {
            YouWant = UserRequest.LET_ME_WIN;
        }

        private void LetMeLose_Click(object sender, RoutedEventArgs e)
        {
            YouWant = UserRequest.LET_ME_LOSE;
        }

        static string PickRandomAnimalName()
        {
            /// <summary>
            /// 随机选取一个动物名字
            /// </summary>
            string[] Animals = { "cat", "dog", "pig" };
            Random Rnd = new Random();
            return Animals[Rnd.Next(0, Animals.Length)];
        }

        class AnimalName : RoutedEventArgs
        {
            private String Name;

            public AnimalName(String _Name)
            {
                Name = _Name;
            }

            public string Args
            {
                get
                {
                    return Name;
                }
            }

        }

    }
}
