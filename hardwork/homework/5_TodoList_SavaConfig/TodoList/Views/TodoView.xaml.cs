using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;
using TodoList.ViewModel; // for TodoManage Class


// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

namespace TodoList.Views
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class TodoView : Page
    {
        public TodoManage AllTodo { get; set; }

        public TodoView()
        {
            this.InitializeComponent();
            this.AllTodo = Application.Current.Resources["Orz"] as TodoManage;
        }

        /// <summary>
        /// QAQ要获取到传过来的Todo
        /// </summary>
        /// <param name="e"></param>
        //protected override void OnNavigatedTo(NavigationEventArgs e)
        //{
        //    if (e.Parameter.GetType() == typeof(TodoManage))
        //    {
        //        this.AllTodo = (TodoManage)(e.Parameter);
        //    }
        //}

        private void EditButton_Click(object sender, RoutedEventArgs e)
        {
            this.AllTodo.OpenEditEvent();
        }
    }
}
