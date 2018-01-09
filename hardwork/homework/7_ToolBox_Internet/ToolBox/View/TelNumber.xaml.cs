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
using System.Net.Http;
using Windows.Data.Xml.Dom;
using Newtonsoft.Json;

// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

namespace ToolBox.View
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class TelNumber : Page
    {
        private string Tel;
        private string Ans;
        private string BackMessage;
        private readonly string Key = "c4415f5c8f654894a31e08b1f375155e";

        public TelNumber()
        {
            this.InitializeComponent();
        }

        private void AppBarButton_Click(object sender, RoutedEventArgs e)
        {
            Tel = InputBox.Text;

            if (UseXML.IsChecked == true)
                SearchUseXML();
            else
                SearchUseJSON();
        }

        private async void SearchUseXML()
        {
            string url = $"http://api.avatardata.cn/MobilePlace/LookUp?key={Key}&mobileNumber={Tel}&dtype=XML&format=true";
            HttpClient client = new HttpClient();
            BackMessage = await client.GetStringAsync(url);
            // BackMessage = "<?xml version=\"1.0\"?>\r\n<MobilePlaceResult>\r\n  <error_code>0</error_code>\r\n  <reason>Succes</reason>\r\n  <result>\r\n    <mobilenumber>1371932</mobilenumber>\r\n    <mobilearea>广东 广州市</mobilearea>\r\n    <mobiletype>移动神州行大众卡</mobiletype>\r\n    <areacode>020</areacode>\r\n    <postcode>510000</postcode>\r\n  </result>\r\n</MobilePlaceResult>";

            XmlDocument document = new XmlDocument();
            document.LoadXml(BackMessage);
            XmlNodeList list = document.GetElementsByTagName("mobilearea");
            IXmlNode node = list.Item(0);
            if (node != null)
                Ans = node.InnerText ?? "";
            else
                Ans = "";

            BackMessageBox.Text = BackMessage;
            OutputBox.Text = Ans;
        }

        private async void SearchUseJSON()
        {
            string url = $"http://api.avatardata.cn/MobilePlace/LookUp?key={Key}&mobileNumber={Tel}&dtype=JSON&format=true";
            HttpClient client = new HttpClient();
            BackMessage = await client.GetStringAsync(url);

            dynamic jsonDe = JsonConvert.DeserializeObject(BackMessage);
            try
            {
                Ans = (string)jsonDe.result.mobilearea ?? "";
            }
            catch
            {
                Ans = "";
            }

            BackMessageBox.Text = BackMessage;
            OutputBox.Text = Ans;
        }
    }
}
