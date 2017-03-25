using TodoList.Views;
using TodoList.ViewModel;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Activation;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.ApplicationModel.ExtendedExecution;
using Windows.UI.Core;
using Windows.Storage;

namespace TodoList
{
    /// <summary>
    /// 提供特定于应用程序的行为，以补充默认的应用程序类。
    /// </summary>
    public sealed partial class App : Application
    {
        public TodoManage AllTodo { get; set; }

        /// <summary>
        /// 初始化单一实例应用程序对象。这是执行的创作代码的第一行，
        /// 已执行，逻辑上等同于 main() 或 WinMain()。
        /// </summary>
        public App()
        {
            this.InitializeComponent();
            this.Resuming += OnResuming;
            this.Suspending += OnSuspending;
            this.AllTodo = new TodoManage();
        }

        protected override void OnLaunched(LaunchActivatedEventArgs e)
        {
            Frame rootFrame = Window.Current.Content as Frame;

            if (rootFrame == null)
            {
                // 创建要充当导航上下文的框架，并导航到第一页
                rootFrame = new Frame();

                rootFrame.NavigationFailed += OnNavigationFailed;

                if (e.PreviousExecutionState == ApplicationExecutionState.Terminated)
                {
                    //TODO: 从之前挂起的应用程序加载状态
                }

                // 将框架放在当前窗口中
                Window.Current.Content = rootFrame;
            }

            if (e.PrelaunchActivated == false)
            {
                if (rootFrame.Content == null)
                {
                    rootFrame.Navigate(typeof(AppShell), e.Arguments);
                }
                Window.Current.Activate();
            }
        }

        void OnNavigationFailed(object sender, NavigationFailedEventArgs e)
        {
            throw new Exception("Failed to load Page " + e.SourcePageType.FullName);
        }

        private async void OnSuspending(object sender, SuspendingEventArgs e)
        {
            var deferral = e.SuspendingOperation.GetDeferral();
            using (var session = new ExtendedExecutionSession())
            {
                session.Reason = ExtendedExecutionReason.SavingData;
                session.Description = "Upload Data";
                //session.Revoked += session_Revoked;
                var result = await session.RequestExtensionAsync();
                if (result == ExtendedExecutionResult.Denied)
                {
                    // OK I hope it will success
                }
                // Upload Data
                TodoManage OrzTodo = Application.Current.Resources["Orz"] as TodoManage;
                await OrzTodo.WriteFileAsync(e);
            }

            deferral.Complete();
        }

        private void OnResuming(object sender, object e)
        {
            // TODO: whatever you need to do to resume your app

        }

    }
}
