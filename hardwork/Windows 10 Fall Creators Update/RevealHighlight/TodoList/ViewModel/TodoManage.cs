using System;                           // for GUID and so on
using System.Windows.Input;             // for ICommand
using Windows.Storage;                  // for Storage
using System.Collections.ObjectModel;   // for ObservableCollection
using Newtonsoft.Json;                  // for JsonVonvert
using Windows.Storage.Pickers;
using Windows.UI.Xaml.Controls;
using System.Threading.Tasks;

namespace TodoList.ViewModel
{
    /*
     * The Most Import Part of this project
     * 
     * About TodoCollection, FileSave/Read, Other Command
     * 
     */

    public class TodoManage : Mvvm.ObservableObject
    {
        #region Properties
        public delegate void OpenView();
        public delegate void OpenEdit();

        private TodoViewModel _SelectTodo;
        private ObservableCollection<TodoViewModel> TodoCollection;

        public OpenView OpenViewEvent;
        public OpenEdit OpenEditEvent;

        public TodoViewModel SelectTodo { get { return _SelectTodo; } set { Set(ref _SelectTodo, value); } }
        public ObservableCollection<TodoViewModel> TodoList { get { return TodoCollection; } set { Set(ref TodoCollection, value); } }

        private bool Busy = false;
        private UpdateTiles.UpdataTiles UpdaterTile;
        private DataBase.DataBase Data;
        #endregion

        #region Contructor
        public TodoManage()
        {
            SelectTodo = default(TodoViewModel);
            UpdaterTile = new UpdateTiles.UpdataTiles();
            Data = new DataBase.DataBase();
            TodoList = Data.select();
        }
        #endregion

        #region Methods
        

        public void SelectTodoInitial()
        {
            SelectTodo.Todo = new Models.TodoClass
            {
                Title = "Title",
                Details = "Details",
                Id = Guid.NewGuid().ToString(),
                DueDate = DateTime.Now
            };
        }

        public void AddTodo()
        {
            TodoViewModel NewTodo = new TodoViewModel();
            this.SelectTodo = NewTodo;
            SelectTodoInitial();
            this.TodoCollection.Add(NewTodo);
            Data.add(NewTodo.Todo);
        }

        public void DeleteTodo(object sender)
        {
            TodoCollection.Remove(SelectTodo);
            Data.delete(SelectTodo.Todo);
        }

        public void ListViewClick(object sender)
        {
            if (SelectTodo != null)
            Data.update(SelectTodo.Todo.Id, SelectTodo.Todo);
            ItemClickEventArgs e = sender as ItemClickEventArgs;
            SelectTodo = (TodoViewModel)e.ClickedItem;
            this.UpdaterTile.UpdataOneTodo(SelectTodo.Todo);
            OpenViewEvent();
        }

        public void SearchTodo(object sender)
        {
            string searchKey = sender as string;
            if (searchKey.Equals(""))
                TodoList = Data.select();
            else
                TodoList = Data.select(searchKey);
        }

        #endregion

        #region Commands

        public ICommand DeleteTodoCommand { get { return new Mvvm.DelegateCommand(DeleteTodo); } }
        public ICommand ListViewClickCommand { get { return new Mvvm.DelegateCommand(ListViewClick); } }

        ICommand _ClearSelectTodoCommand = default(ICommand);
        public ICommand ClearSelectTodoCommand
        {
            get
            {
                return _ClearSelectTodoCommand ?? (
                    _ClearSelectTodoCommand = new Mvvm.DelegateCommand(
                        ExecuteClearSelectTodoCommand, CanExecuteClearSelectTodoCommand));
            }
        }
        private bool CanExecuteClearSelectTodoCommand(object sender) { return true; }
        private void ExecuteClearSelectTodoCommand(object sender)
        {
            SelectTodoInitial();
        }

        ICommand _SearchCommand = default(ICommand);
        public ICommand SearchCommand
        {
            get
            {
                return _SearchCommand ?? (
                    _SearchCommand = new Mvvm.DelegateCommand(
                        ExecuteSearchCommand, CanExecuteSearchCommand));
            }
        }
        private bool CanExecuteSearchCommand(object sender) { return true; }
        private void ExecuteSearchCommand(object sender)
        {
            SelectTodoInitial();
        }

        ICommand _SelectPictureCommand = default(ICommand);
        public ICommand SelectPictureCommand
        {
            get
            {
                return _SelectPictureCommand ?? (
                    _SelectPictureCommand = new Mvvm.DelegateCommand(
                        ExecuteSelectPictureCommand, CanExecuteSelectPictureCommand));
            }
        }
        private bool CanExecuteSelectPictureCommand(object sender) { return !Busy; }
        private async void ExecuteSelectPictureCommand(object sender)
        {
            try
            {
                Busy = true;

                FileOpenPicker openPicker = new FileOpenPicker();
                openPicker.ViewMode = PickerViewMode.Thumbnail;
                openPicker.SuggestedStartLocation = PickerLocationId.PicturesLibrary;
                openPicker.FileTypeFilter.Add(".jpg");
                openPicker.FileTypeFilter.Add(".jpeg");
                openPicker.FileTypeFilter.Add(".png");

                StorageFile file = await openPicker.PickSingleFileAsync();

                if (file != null)
                {
                    // Copy the file into local folder
                    await file.CopyAsync(ApplicationData.Current.LocalFolder, file.Name, NameCollisionOption.ReplaceExisting);
                    // Save in the ToDoItem
                    SelectTodo.Todo.ImageUri = new Uri("ms-appdata:///local/" + file.Name);
                }
            }
            finally { Busy = false; }
        }

        #endregion
    }
}
