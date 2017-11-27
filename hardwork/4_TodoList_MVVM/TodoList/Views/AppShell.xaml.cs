using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using TodoList.ViewModel;
using Windows.UI.Xaml.Navigation;
using Windows.Storage;

namespace TodoList.Views
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class AppShell : Page
    {
        private TodoManage Todo;

        public AppShell()
        {
            this.InitializeComponent();
            this.Todo = Application.Current.Resources["Orz"] as TodoManage;
            this.Todo.OpenViewEvent += () => { SideFrame.Navigate(typeof(TodoView), Todo); };
            this.Todo.OpenEditEvent += () => { SideFrame.Navigate(typeof(TodoEdit), Todo); };

            MainFrame.Navigate(typeof(AppView));
            SideFrame.Navigate(typeof(NeedTodo));

            Windows.UI.Core.SystemNavigationManager.GetForCurrentView().BackRequested += OnBackRequested;

            SideFrame.Navigated += (s, a) =>
            {
                if (SideFrame.CanGoBack)
                {
                    // Setting this visible is ignored on Mobile and when in tablet mode!     
                    Windows.UI.Core.SystemNavigationManager.GetForCurrentView().AppViewBackButtonVisibility = Windows.UI.Core.AppViewBackButtonVisibility.Visible;
                    if (SideFrameColumn.Width.Value == 0) Grid.SetColumn(SideFrame, 1);
                }
                else
                {
                    Windows.UI.Core.SystemNavigationManager.GetForCurrentView().AppViewBackButtonVisibility = Windows.UI.Core.AppViewBackButtonVisibility.Collapsed;
                }
            };
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Todo.AddTodo();
            SideFrame.Navigate(typeof(TodoEdit));
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            SideFrame.Navigate(typeof(Setting));
        }

        private void OnBackRequested(object sender, Windows.UI.Core.BackRequestedEventArgs e)
        {
            if (SideFrame == null)
                return;
            // Navigate back if possible, and if the event has not 
            // already been handled .
            while (SideFrame.CanGoBack && e.Handled == false)
            {
                SideFrame.GoBack();
                Grid.SetColumn(SideFrame, 2);
            }
            e.Handled = true;
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            if (ApplicationData.Current.LocalSettings.Values.ContainsKey("SideFrame"))
            {
                switch ((string)ApplicationData.Current.LocalSettings.Values["SideFrame"])
                {
                    case "Setting":
                        SideFrame.Navigate(typeof(Setting));
                        break;
                }
                ApplicationData.Current.LocalSettings.Values.Remove("SideFrame");
            }
        }
    }
}
