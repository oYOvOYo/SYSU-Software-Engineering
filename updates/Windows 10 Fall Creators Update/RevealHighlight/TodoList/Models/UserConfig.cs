using Newtonsoft.Json;                  // for [JsonProperty]

namespace TodoList.Models
{
    /// <summary>
    /// TodoItem Class from ObservableObject
    /// </summary>
    public class UserConfig : Mvvm.ObservableObject
    {
        // I just set id, title, details, due_time image_url those properties
        // [JsonProperty(PropertyName="name")] is used in Json

        private string _UserName = default(string);
        [JsonProperty(PropertyName = "title")]
        public string UserName { get { return _UserName; } set { Set(ref _UserName, value); } }
    }
}