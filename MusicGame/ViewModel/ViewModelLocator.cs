using GalaSoft.MvvmLight;
using GalaSoft.MvvmLight.Ioc;
using GalaSoft.MvvmLight.Views;
using Microsoft.Practices.ServiceLocation;
using MusicGame.Models;

namespace MusicGame.ViewModel
{
    /// <summary>
    /// This class contains static references to all the view models in the
    /// application and provides an entry point for the bindings.
    /// <para>
    /// See http://www.mvvmlight.net
    /// </para>
    /// </summary>
    public class ViewModelLocator
    {
        private const string shellKey = nameof(Views.AppShell);
        private const string settingsKey = nameof(Views.Settings);
        private const string homeKey = nameof(Views.Home);

        public static string HomeKey => homeKey;
        public static string SettingsKey => settingsKey;
        public static string ShellKey => shellKey;

        public MainViewModel Main => ServiceLocator.Current.GetInstance<MainViewModel>();
        public UserConfigViewModel Config => ServiceLocator.Current.GetInstance<UserConfigViewModel>();
        public MusicGameViewModel MusicGame => ServiceLocator.Current.GetInstance<MusicGameViewModel>();

        static ViewModelLocator()
        {
            ServiceLocator.SetLocatorProvider(() => SimpleIoc.Default);

            var nav = new NavigationService();
            nav.Configure(ShellKey, typeof(Views.AppShell));
            nav.Configure(HomeKey, typeof(Views.Home));
            nav.Configure(SettingsKey, typeof(Views.Settings));
            SimpleIoc.Default.Register<INavigationService>(() => nav);

            SimpleIoc.Default.Register<UserConfigServer>();
            SimpleIoc.Default.Register<FilesServer>();

            SimpleIoc.Default.Register<MainViewModel>();
            SimpleIoc.Default.Register<UserConfigViewModel>();
            SimpleIoc.Default.Register<MusicGameViewModel>();
        }
    }
}
