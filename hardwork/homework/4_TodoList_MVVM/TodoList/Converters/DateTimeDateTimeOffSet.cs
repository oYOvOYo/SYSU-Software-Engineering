using System;
using Windows.UI.Xaml.Data;

namespace TodoList.Converters
{
    /*
        How to Write a Converter Class
        Just write a Class from IValueConverter
        and finish two Function name Convert and ConvertBack

        As about the func arguements:
        Return value should be object (the univeral type 2333
        and recive A lot of arguement, I think now I just use value..

        really too long to remmember
    */
    public class DateTimeToDateTimeOffsetConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            // value -> return value
            try
            {
                DateTime date = (DateTime)value;
                return new DateTimeOffset(date);
            }

            catch (Exception)
            {
                return DateTimeOffset.MinValue;
            }
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            // value to return value
            try
            {
                DateTimeOffset dto = (DateTimeOffset)value;
                return dto.DateTime;
            }
            catch (Exception)
            {
                return DateTime.MinValue;
            }
        }
    }
}