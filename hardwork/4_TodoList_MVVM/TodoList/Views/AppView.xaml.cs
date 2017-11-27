using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;
using TodoList.Models;
using TodoList.ViewModel;
using System;
using Windows.UI.Xaml;

namespace TodoList.Views
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class AppView : Page
    {
        private TodoManage Todo;

        public AppView()
        {
            this.InitializeComponent();
            this.Todo = Application.Current.Resources["Orz"] as TodoManage;
        }

        private void ListView_ItemClick(object sender, ItemClickEventArgs e)
        {
            Todo.SelectTodo = (TodoClass)e.ClickedItem;
            Todo.OpenViewEvent();
        }
    }
}
