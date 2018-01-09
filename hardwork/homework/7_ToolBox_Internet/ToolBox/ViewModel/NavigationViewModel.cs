using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using Windows.UI.Xaml.Controls;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ToolBox.ViewModel
{

    public class NavigationViewModel
    {

        public delegate void MainFrameNavigate();
        public MainFrameNavigate MainFrameNavigateEvent;

        private ObservableCollection<Navigation.INavigationItem> _NavigationCollection;
        private Navigation.INavigationItem _SelectNavigationItem;

        public ObservableCollection<Navigation.INavigationItem> NavigationCollection
        {
            get { return _NavigationCollection; }
            set { _NavigationCollection = value; }
        }

        public Navigation.INavigationItem SelectNavigationItem
        {
            get { return _SelectNavigationItem; }
            set { _SelectNavigationItem = value; }
        }


        public NavigationViewModel()
        {
            SelectNavigationItem = default(Navigation.INavigationItem);
            NavigationCollection = new ObservableCollection<Navigation.INavigationItem>();
            NavigationCollection.Add(new Navigation.INavigationItem()
            {
                Label = "Home",
                Symbol = Symbol.Home,
                DestPage = typeof(View.Welcome)
            });

            NavigationCollection.Add(new Navigation.INavigationItem()
            {
                Label = "Regex",
                Symbol = Symbol.Find,
                DestPage = typeof(View.Regex)
            });

            NavigationCollection.Add(new Navigation.INavigationItem()
            {
                Label = "Tel Number",
                Symbol = Symbol.Contact2,
                DestPage = typeof(View.TelNumber)
            });

        }

        public void ListViewClick(object sender)
        {
            ItemClickEventArgs e = sender as ItemClickEventArgs;
            SelectNavigationItem = (Navigation.INavigationItem)e.ClickedItem;
            MainFrameNavigateEvent();
        }

    }
}
