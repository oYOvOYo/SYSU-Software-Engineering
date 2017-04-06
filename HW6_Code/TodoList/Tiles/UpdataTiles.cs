using System;
using System.Net;
using Windows.Data.Xml.Dom;
using Windows.Storage;
using Windows.UI.Notifications;

namespace TodoList.UpdateTiles
{
    class UpdataTiles
    {

        private string XmlData;

        public UpdataTiles()
        {
            ReadFile();
        }

        private async void ReadFile()
        {
            var file = await StorageFile.GetFileFromApplicationUriAsync(new Uri("ms-appx:///Tiles/Tiles.xml"));
            XmlData = await FileIO.ReadTextAsync(file);
        }

        public void UpdataOneTodo(Models.TodoClass Todo)
        {
            var doc = new XmlDocument();
            var xml = string.Format(XmlData, Todo.Title, Todo.Details, Todo.ImageUri);
            var update = TileUpdateManager.CreateTileUpdaterForApplication();
            update.EnableNotificationQueue(true);

            doc.LoadXml(WebUtility.HtmlDecode(xml), new XmlLoadSettings
            {
                ProhibitDtd = false,
                ValidateOnParse = false,
                ElementContentWhiteSpace = false,
                ResolveExternals = false
            });

            update.Update(new TileNotification(doc));
        }

    }

}
