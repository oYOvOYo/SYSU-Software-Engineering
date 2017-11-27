using System;                           // for DateTime and so on
using Newtonsoft.Json;                  // for [JsonProperty]
using Windows.UI.Xaml.Media.Imaging;    // now no use
using TodoList.Mvvm;                    // for DelegateCommand
using System.Windows.Input;             // for ICommand


namespace TodoList.Models
{
    /// <summary>
    /// TodoItem Class from ObservableObject
    /// </summary>
    public class TodoClass : ObservableObject
    {
        // I just set id, title, details, due_time image_url those properties
        // [JsonProperty(PropertyName="name")] is used in Json

        private string _Id = default(string);
        public string Id { get { return _Id; } set { Set(ref _Id, value); } }

        private string _Title = default(string);
        [JsonProperty(PropertyName = "title")]
        public string Title { get { return _Title; } set { Set(ref _Title, value); } }

        private string _Details = default(string);
        [JsonProperty(PropertyName = "details")]
        public string Details { get { return _Details; } set { Set(ref _Details, value); } }

        private DateTime _DueDate = default(DateTime);
        [JsonProperty(PropertyName = "dueDate")]
        public DateTime DueDate { get { return _DueDate; } set { Set(ref _DueDate, value); } }

        private bool _IsComplete = default(bool);
        [JsonProperty(PropertyName = "isComplete")]
        public bool IsComplete { get { return _IsComplete; } set { Set(ref _IsComplete, value); } }

        private Uri _ImageUri = default(Uri);
        public Uri ImageUri { get { return _ImageUri; } set { Set(ref _ImageUri, value); } }

        /// <summary>
        /// Set Finished to reverse value
        /// </summary>
        /// <param name="sender">No Use, Just set</param>
        private void ChangeComplete(object sender) { IsComplete = ! IsComplete; }

        // return a ICommand type object
        public ICommand ChangeCompleteCommand { get { return new DelegateCommand(ChangeComplete); } }
    }
}
