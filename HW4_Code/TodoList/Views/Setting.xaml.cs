using Windows.ApplicationModel;
using Windows.Storage;
using Windows.UI.Core;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;


// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

namespace TodoList.Views
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class Setting : Page
    {
        public Setting()
        {
            this.InitializeComponent();
            this.UserConfigViewModel = new ViewModel.UserConfigViewModel();
            this.UserConfigViewModel.LoadData();
        }

        ViewModel.UserConfigViewModel UserConfigViewModel { get; set; }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            ((App)App.Current).Suspending += SaveSetting;
            ((App)App.Current).Suspending += SaveSideFrameInfo;
            Windows.UI.Core.SystemNavigationManager.GetForCurrentView().BackRequested += SaveSetting;
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            ((App)App.Current).Suspending -= SaveSetting;
            ((App)App.Current).Suspending -= SaveSideFrameInfo;
            Windows.UI.Core.SystemNavigationManager.GetForCurrentView().BackRequested -= SaveSetting;
        }

        private void SaveSetting(object sender, object e)
        {
            this.UserConfigViewModel.SaveData();
        }

        private void SaveSideFrameInfo(object sender, object e)
        {
            ApplicationData.Current.LocalSettings.Values["SideFrame"] = "Setting";
        }
    }
}
