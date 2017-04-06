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

    public class TodoManage
    {
        #region Properties
        public delegate void OpenView();
        public delegate void OpenEdit();

        private ViewModel.TodoViewModel _SelectTodo;
        private ObservableCollection<ViewModel.TodoViewModel> TodoCollection;

        public OpenView OpenViewEvent;
        public OpenEdit OpenEditEvent;

        public ViewModel.TodoViewModel SelectTodo { get { return _SelectTodo; } set { _SelectTodo = value; } }
        public ObservableCollection<ViewModel.TodoViewModel> TodoList { get { return TodoCollection; } }

        private bool Busy = false;
        private UpdateTiles.UpdataTiles UpdaterTile;
        #endregion

        #region Contructor
        public TodoManage()
        {
            _SelectTodo = default(ViewModel.TodoViewModel);
            ReadFile();
        }
        #endregion

        #region Methods
        private async void ReadFile()
        {
            try
            {
                StorageFolder Folder = ApplicationData.Current.LocalFolder;
                StorageFile InFile = await Folder.GetFileAsync("data");
                string Json = await FileIO.ReadTextAsync(InFile);
                if (Json == "")
                {
                    TodoCollection = new ObservableCollection<ViewModel.TodoViewModel>();
                    TodoCollection.Add(new ViewModel.TodoViewModel());
                    TodoCollection.Add(new ViewModel.TodoViewModel());
                } else
                {
                    TodoCollection = JsonConvert.DeserializeObject<ObservableCollection<ViewModel.TodoViewModel>>(Json);
                }
            }
            catch
            {
                TodoCollection = new ObservableCollection<ViewModel.TodoViewModel>();
                TodoCollection.Add(new ViewModel.TodoViewModel());
                TodoCollection.Add(new ViewModel.TodoViewModel());
            }

            this.UpdaterTile = new UpdateTiles.UpdataTiles();
        }

        public async void WriteFile(object sender)
        {
            StorageFolder Folder = ApplicationData.Current.LocalFolder;
            StorageFile OutFile = await Folder.CreateFileAsync("data",
                CreationCollisionOption.ReplaceExisting);
            string Json = JsonConvert.SerializeObject(TodoCollection, Formatting.Indented);
            await FileIO.WriteTextAsync(OutFile, Json);
        }

        public async Task WriteFileAsync(object sender)
        {
            StorageFolder Folder = ApplicationData.Current.LocalFolder;
            StorageFile OutFile = await Folder.CreateFileAsync("data",
                CreationCollisionOption.ReplaceExisting);
            string Json = JsonConvert.SerializeObject(TodoCollection, Formatting.Indented);
            await FileIO.WriteTextAsync(OutFile, Json);
        }

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
            ViewModel.TodoViewModel NewTodo = new ViewModel.TodoViewModel();
            this.SelectTodo = NewTodo;
            SelectTodoInitial();
            this.TodoCollection.Add(NewTodo);
        }

        public void ListViewClick(object sender)
        {
            ItemClickEventArgs e = sender as ItemClickEventArgs;
            SelectTodo = (ViewModel.TodoViewModel)e.ClickedItem;
            this.UpdaterTile.UpdataOneTodo(SelectTodo.Todo);
            OpenViewEvent();
        }

        public void DeleteTodo(object sender)
        {
            TodoCollection.Remove(SelectTodo);
        }

        #endregion

            #region Commands

        public ICommand DeleteTodoCommand { get { return new Mvvm.DelegateCommand(DeleteTodo); } }
        public ICommand SaveFileCommand { get { return new Mvvm.DelegateCommand(WriteFile); } }
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
