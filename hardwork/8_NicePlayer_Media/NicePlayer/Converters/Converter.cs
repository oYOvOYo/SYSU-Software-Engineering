using System;
using Windows.UI.Xaml.Data;

namespace NicePlayer.Converters
{
    public class ValueConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            return ((TimeSpan)value).TotalSeconds;
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            return TimeSpan.FromSeconds((double)value);
        }
    }


    public class DoubleHeightConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            return ((Double)value) * 3;
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            return ((Double)value) * 0.5;
        }
    }

    public class isPlayingConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            return (Windows.UI.Xaml.Media.MediaElementState)value == Windows.UI.Xaml.Media.MediaElementState.Playing;
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            return Windows.UI.Xaml.Media.MediaElementState.Playing;
        }
    }
}