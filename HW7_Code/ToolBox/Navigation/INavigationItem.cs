using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Xaml.Controls;

namespace ToolBox.Navigation
{
    public class INavigationItem : Mvvm.ObservableObject
    {

        private string _Label = default(string);
        public string Label { get { return _Label; } set { Set(ref _Label, value); } }

        private Symbol _Symbol;
        public Symbol Symbol { get { return _Symbol; } set { Set(ref _Symbol, value); } }

        private Type _DestPage;
        public Type DestPage { get { return _DestPage; } set { Set(ref _DestPage, value); } }
    }
}
