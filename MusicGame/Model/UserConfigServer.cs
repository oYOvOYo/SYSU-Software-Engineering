using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Storage;

namespace MusicGame.Model
{
    public class UserConfigServer
    {
        public Task<UserConfig> GetConfig()
        {
            UserConfig Config;
            if (ApplicationData.Current.RoamingSettings.Values.ContainsKey("Config"))
            {
                var JsonStr = ApplicationData.Current.RoamingSettings.Values["Config"].ToString();
                Config = JsonConvert.DeserializeObject<UserConfig>(JsonStr);
            }
            else
            {
                Config = new UserConfig()
                {
                    RoundNumber = 4,
                    EachRoundChoicesNumber = 6,
                    DifficultyIncreased = false,
                    FolderPath = KnownFolders.MusicLibrary.Path
                };
            }

            return Task.FromResult(Config);
        }

        public void SaveConfig(UserConfig Config)
        {
            ApplicationData.Current.RoamingSettings.Values["Config"] = JsonConvert.SerializeObject(Config);
        }
    }
}
