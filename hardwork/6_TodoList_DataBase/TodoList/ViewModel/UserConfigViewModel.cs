using Windows.Storage;                  // for Storage
using TodoList.Models;                  // for TodoClass
using Newtonsoft.Json;                  // for JsonVonvert

namespace TodoList.ViewModel
{
    /*
     * The Most Import Part of this project
     * 
     * About TodoCollection, FileSave/Read, Other Command
     * 
     */

    public class UserConfigViewModel : Mvvm.ObservableObject
    {
        private Models.UserConfig _UserConfig;
        public Models.UserConfig UserConfig
        {
            get { return _UserConfig; }
            set { Set(ref _UserConfig, value); }
        }

        #region Methods for handling the apps permanent data
        public void LoadData()
        {
            if (ApplicationData.Current.RoamingSettings.Values.ContainsKey("UserConfig"))
            {
                this.UserConfig = JsonConvert.DeserializeObject<UserConfig>(
                    (string)ApplicationData.Current.RoamingSettings.Values["UserConfig"]);
            }
            else
            {
                this.UserConfig = new UserConfig();
            }
        }

        public void SaveData()
        {
            ApplicationData.Current.RoamingSettings.Values["UserConfig"] =
                JsonConvert.SerializeObject(this.UserConfig);
        }
        #endregion
    }
}
