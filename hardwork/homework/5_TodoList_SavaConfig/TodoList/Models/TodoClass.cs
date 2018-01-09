using System;                           // for DateTime and so on
using Newtonsoft.Json;                  // for [JsonProperty]
using Windows.UI.Xaml.Media.Imaging;    // now no use
using System.Windows.Input;             // for ICommand
using Windows.ApplicationModel.DataTransfer;
using Windows.Storage;
using System.Collections.Generic;

namespace TodoList.Models
{
    /// <summary>
    /// TodoItem Class from ObservableObject
    /// </summary>
    public class TodoClass : Mvvm.ObservableObject
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

    }
}
