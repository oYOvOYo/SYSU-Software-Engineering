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

//“空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409 上有介绍

namespace HomeWork1
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        // 声明事件处理的委托
        private delegate void AnimalSpeak(string SpeakerName, bool ClearTextBox);
        // 根据委托声明事件
        private event AnimalSpeak SpeakEvent;
        // 三个AnimalSpeaker的实例
        private AnimalSpeaker cat, dog, pig;
        

        public MainPage()
        {
            this.InitializeComponent();
            // 初始化实例
            cat = new AnimalSpeaker("cat", OutputText, InputText);
            dog = new AnimalSpeaker("dog", OutputText, InputText);
            pig = new AnimalSpeaker("pig", OutputText, InputText);
            // 将委托函数交给事件
            SpeakEvent += new AnimalSpeak(cat.Speak);
            SpeakEvent += new AnimalSpeak(dog.Speak);
            SpeakEvent += new AnimalSpeak(pig.Speak);
        }

        static string AnimalSpeakContent(string AnimalName)
        {
            /// <summary>
            /// 产生动物说话内容
            /// </summary>
            string SpeakContent = AnimalName.ToUpper()[0].ToString() + AnimalName.Substring(1) + ": I am " + AnimalName + ".\n";
            return SpeakContent;
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

        interface Animal
        {
            // 动物接口，只设置发言一个方法
            void Speak(string SpeakerName, bool ClearTextBox);
        }

        class AnimalSpeaker : Animal
        {
            // 动物类
            private String AnimalName;      // 动物名称
            private TextBox ClearTarget;    // 清理目标
            private TextBlock SpeakTarget;  // 发言目标

            public AnimalSpeaker(String AnimalName, TextBlock OutputTarget, TextBox InputTarget)
            {
                // 构造函数，初始化私有变量
                this.AnimalName = AnimalName;
                this.SpeakTarget = OutputTarget;
                this.ClearTarget = InputTarget;
            }

            public void Speak(string SpeakerName, bool ClearTextBox)
            {
                // 当发言人是该动物时
                if (SpeakerName == AnimalName)
                {
                    // 发言
                    SpeakTarget.Text += AnimalSpeakContent(AnimalName);
                    // 如果要求清空输入框
                    if (ClearTextBox)
                    {
                        ClearTarget.Text = "";
                    }
                }
            }
        }

        private void SpeakButton_Click(object sender, RoutedEventArgs e)
        {
            // 点击Speak按钮处理函数
            SpeakEvent(PickRandomAnimalName(), false);
        }

        private void OKButton_Click(object sender, RoutedEventArgs e)
        {
            // 点击OK按钮处理函数
            SpeakEvent(InputText.Text, true);
        }

        private void HyperlinkButton_Click(object sender, RoutedEventArgs e)
        {
            // 跳转到Main.xaml
            this.Frame.Navigate(typeof(Main));
        }
    }
}
