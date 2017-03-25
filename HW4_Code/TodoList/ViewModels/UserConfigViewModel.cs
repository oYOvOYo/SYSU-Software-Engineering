using System;                           // for GUID and so on
using System.Windows.Input;             // for ICommand
using Windows.Storage;                  // for Storage
using TodoList.Mvvm;                    // for DelegateCommand
using TodoList.Models;                  // for TodoClass
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
