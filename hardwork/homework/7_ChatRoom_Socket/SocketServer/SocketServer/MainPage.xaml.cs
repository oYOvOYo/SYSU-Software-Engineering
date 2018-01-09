using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
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

namespace SocketServer
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {

        public StreamSocketListener ServerListener;
        private List<StreamSocket> ClientSockets;

        public MainPage()
        {
            this.InitializeComponent();
            ServerListener = new StreamSocketListener();
            ClientSockets = new List<StreamSocket>();
            RunServer();
        }

        private async void RunServer()
        {
            try
            {
                ServerListener.ConnectionReceived += OnConnection;
                await ServerListener.BindEndpointAsync(new HostName("192.168.199.110"), "8000");
                Output.Text = "启动成功";
            }
            catch
            {
                Output.Text = "启动失败，请重启应用";
            }
        }

        private async void OnConnection(StreamSocketListener sender, StreamSocketListenerConnectionReceivedEventArgs args)
        {
            StreamSocket ClientSocket = args.Socket;
            ClientSockets.Add(ClientSocket);
            var Reader = new DataReader(ClientSocket.InputStream);
            Reader.InputStreamOptions = InputStreamOptions.Partial;
            while (true)
            {
               try
               {
                    await Reader.LoadAsync(1024);
                    string str = Reader.ReadString(Reader.UnconsumedBufferLength);
                    str = ClientSocket.Information.RemoteAddress + " : " +str;
                    await this.Dispatcher.RunAsync(Windows.UI.Core.CoreDispatcherPriority.Normal, () =>
                    {
                        this.Output.Text += ("\n" + str);
                    });
                    SendBroadcast(str);
               }

                catch
                {

                }
            }
            
        }


        private void Close_Click(object sender, RoutedEventArgs e)
        {
            // the Close()  is not implemented in C#
            // see https://docs.microsoft.com/en-us/uwp/api/windows.networking.sockets.streamsocketlistener
        }

        private void Broadcast_Click(object sender, RoutedEventArgs e)
        {
            string str = "\nServer : " + Input.Text;
            this.Output.Text += (str);
            SendBroadcast(str);
        }

        private void SendBroadcast(string Message)
        {
            foreach (StreamSocket ClientSocket in ClientSockets)
            {
                SendMessage(ClientSocket, Message);
            }
        }

        private async void SendMessage(StreamSocket Socket, string Message)
        {
            var Write = new DataWriter(Socket.OutputStream);
            Write.WriteString(Message);
            await Write.StoreAsync();
        }

    }
}
