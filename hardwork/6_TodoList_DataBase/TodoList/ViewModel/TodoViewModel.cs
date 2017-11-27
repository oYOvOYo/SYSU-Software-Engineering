using System;
using System.Collections.Generic;
using System.Windows.Input;
using Windows.ApplicationModel.DataTransfer;
using Windows.Storage;

namespace TodoList.ViewModel
{
    public class TodoViewModel : Mvvm.ObservableObject
    {
        private Models.TodoClass _Todo;
        public Models.TodoClass Todo
        {
            get { return _Todo; }
            set { Set(ref _Todo, value); }
        }

        public TodoViewModel()
        {
            this.Todo = new Models.TodoClass
            {
                Title = "Title",
                Details = "Details",
                Id = Guid.NewGuid().ToString(),
                DueDate = DateTime.Now
            };
        }

        private void ChangeComplete(object sender) { Todo.IsComplete = !Todo.IsComplete; }

        public Boolean ContainStr(string str) { return (Todo.Title + Todo.Details).Contains(str); }

        #region Command

        public void ShareTodo(object sender)
        {
            DataTransferManager.GetForCurrentView().DataRequested += OnShareDataRequested;
            DataTransferManager.ShowShareUI();
        }

        private async void OnShareDataRequested(DataTransferManager sender, DataRequestedEventArgs args)
        {
            var request = args.Request;
            request.Data.Properties.Title = Todo.Title;
            request.Data.Properties.Description = "Todo Share";
            request.Data.SetText(Todo.Details);
            if (Todo.ImageUri != null)
            {
                var photoFile = await StorageFile.GetFileFromApplicationUriAsync(Todo.ImageUri);
                request.Data.SetStorageItems(new List<StorageFile> { photoFile });
            }
            DataTransferManager.GetForCurrentView().DataRequested -= OnShareDataRequested;
        }

        // return a ICommand type object
        public ICommand ChangeCompleteCommand { get { return new Mvvm.DelegateCommand(ChangeComplete); } }
        public ICommand ShareTodoCommand { get { return new Mvvm.DelegateCommand(ShareTodo); } }
        #endregion

    }

}