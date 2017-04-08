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

// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

namespace ToolBox.View
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class AppShell : Page
    {

        private ViewModel.NavigationViewModel NavigationViewModel;

        public AppShell()
        {
            this.InitializeComponent();
            this.NavigationViewModel =
                Application.Current.Resources["NavigationViewModel"] as ViewModel.NavigationViewModel;
            this.NavigationViewModel.MainFrameNavigateEvent += () =>
            {
                MainFrame.Navigate(this.NavigationViewModel.SelectNavigationItem.DestPage);
            };
        }

        private void ListView_ItemClick(object sender, ItemClickEventArgs e)
        {
            this.NavigationViewModel.ListViewClick(e);
        }
    }
}
