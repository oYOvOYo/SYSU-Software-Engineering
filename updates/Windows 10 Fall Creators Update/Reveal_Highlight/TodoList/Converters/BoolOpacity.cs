using System;
using Windows.UI.Xaml.Data;

namespace TodoList.Converters
{

    public class BoolOpacityConverter : IValueConverter
    {
        // Define the Convert method to convert a bool value to double
        public object Convert(object value, Type targetType,
            object parameter, string language)
        {
            // value is the data from the source object.
            bool Opacity = ((bool)value);

            // Return the value to pass to the target.
            if (Opacity)
            {
                return 1.0;
            }
            else
            {
                return 0.0;
            }
        }

        // ConvertBack is not implemented for a OneWay binding.
        public object ConvertBack(object value, Type targetType,
            object parameter, string language)
        {
            // value is the data from the source object.
            bool Opacity = ((bool)value);

            // Return the value to pass to the target.
            if (Opacity)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}
