using System;
using System.Threading.Tasks;
using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Command;
using GalaSoft.MvvmLight.Messaging;
using GalaSoft.MvvmLight.Threading;
using GalaSoft.MvvmLight.Views;
using Microsoft.Practices.ServiceLocation;
using MusicGame.Models;

namespace MusicGame.ViewModel
{
    public class MainViewModel : ViewModelBase
    {
        private readonly INavigationService _navigationService;
        private RelayCommand<string> _navigateCommand;
        //private RelayCommand _sendMessageCommand;
        //private RelayCommand _showDialogCommand;

        public RelayCommand<string> NavigateCommand
        {
            get
            {
                return _navigateCommand
                       ?? (_navigateCommand = new RelayCommand<string>(
                           p => _navigationService.NavigateTo(ViewModelLocator.ShellKey, p),
                           p => !string.IsNullOrEmpty(p)));
            }
        }

        //public RelayCommand SendMessageCommand
        //{
        //    get
        //    {
        //        return _sendMessageCommand
        //            ?? (_sendMessageCommand = new RelayCommand(
        //            () =>
        //            {
        //                Messenger.Default.Send(
        //                    new NotificationMessageAction<string>(
        //                        "Testing",
        //                        reply =>
        //                        {
        //                        }));
        //            }));
        //    }
        //}

        //public RelayCommand ShowDialogCommand
        //{
        //    get
        //    {
        //        return _showDialogCommand
        //               ?? (_showDialogCommand = new RelayCommand(
        //                   async () =>
        //                   {
        //                       var dialog = ServiceLocator.Current.GetInstance<IDialogService>();
        //                       await dialog.ShowMessage("Hello Universal Application", "it works...");
        //                   }));
        //    }
        //}

        public MainViewModel(
            INavigationService navigationService)
        {
            _navigationService = navigationService;
        }
    }
}