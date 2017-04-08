using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using System.Text.RegularExpressions;

// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

namespace ToolBox.View
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class Regex : Page
    {
        public Regex()
        {
            this.InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            string input = Input.Text;
            string regex = ReInput.Text;
            string ans = "";

            try
            {
                foreach (Match match in System.Text.RegularExpressions.Regex.Matches(input, regex))
                {
                    ans += match.Value;
                    ans += "\n";
                }

            }
            catch (ArgumentNullException)
            {
                ans = "ArgumentNullException : input 为 null。";
            }
            catch (RegexMatchTimeoutException)
            {
                ans = "RegexMatchTimeoutException : 发生超时。";
            }
            finally
            {
                Output.Text = ans;
            }
        }
    }
}
