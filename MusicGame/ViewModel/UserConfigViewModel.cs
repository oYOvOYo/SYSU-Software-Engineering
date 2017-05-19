using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Command;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MusicGame.Model;
using Windows.Storage.Pickers;

namespace MusicGame.ViewModel
{
    public class UserConfigViewModel : ViewModelBase
    {
        private Model.UserConfigServer _userConfigServer;
        private Model.UserConfig _userConfig;
        private RelayCommand _chooseFolderCommand;

        public UserConfig UserConfig
        {
            get => _userConfig;
            set => _userConfig = value;
        }

        public RelayCommand ChooseFolderCommand
        {
            get
            {
                return _chooseFolderCommand ??
                    (_chooseFolderCommand = new RelayCommand(
                        async () =>
                        {
                            FolderPicker picker = new FolderPicker();
                            picker.FileTypeFilter.Add(".");
                            var folder = await picker.PickSingleFolderAsync();
                            if (folder != null) UserConfig.FolderPath = folder.Path;
                        }));
            }
        }

        public UserConfigViewModel(Model.UserConfigServer userConfigServer)
        {
            _userConfigServer = userConfigServer;
            InitialConfig();
        }

        public async Task InitialConfig()
        {
            UserConfig = await _userConfigServer.GetConfig();
        }
    }
}
