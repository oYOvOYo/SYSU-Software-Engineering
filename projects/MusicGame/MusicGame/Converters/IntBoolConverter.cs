using System;
using Windows.UI.Xaml.Data;

namespace MusicGame.Converters
{
    public class IntBoolConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            return value.ToString() == (string)parameter;
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            return Int32.Parse((string)parameter);
        }
    }
}
