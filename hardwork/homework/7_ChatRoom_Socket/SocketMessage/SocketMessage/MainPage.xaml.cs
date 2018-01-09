using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading.Tasks;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Networking;
using Windows.Networking.Sockets;
using Windows.Storage.Streams;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x804 上介绍了“空白页”项模板

namespace SocketMessage
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public StreamSocket Socket;

        public MainPage()
        {
            this.InitializeComponent();
            RunClient();
            Task.Run(async () =>
            {
                var reader = new DataReader(Socket.InputStream);
                reader.InputStreamOptions = InputStreamOptions.Partial;

                while (true)
                {
                    await reader.LoadAsync(1024);
                    string str = reader.ReadString(reader.UnconsumedBufferLength);
                    await this.Dispatcher.RunAsync(Windows.UI.Core.CoreDispatcherPriority.Normal, () =>
                    {
                        this.Text.Text = Text.Text + ("\n" + str);
                    });
                }

            });
        }

        private async void RunClient()
        {
            try
            {
                Socket = new StreamSocket();
                HostName Host = new HostName("192.168.199.110");
                string Port = "8000";
                await Socket.ConnectAsync(Host, Port);
                Text.Text = "连接成功";
            }
            catch
            {
                Text.Text = "连接失败，请重启应用";
            }

        }

        private async void Write(string str)
        {
            var writer = new DataWriter(Socket.OutputStream);
            writer.WriteString(str);
            //异步发送数据
            await writer.StoreAsync();
        }


        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Write(Input.Text);
        }

    }
}
