using System;
using Windows.Storage;

namespace TodoList.FileServer
{
    public class FileServer
    {
        #region Properties
        private StorageFolder _FileFolder;
        public StorageFolder FileFolder { get { return _FileFolder; } set { _FileFolder = value; } }

        private string _FileName;
        public string FileName { get { return _FileName; } set { FileName = value; } }
        #endregion

        #region Contructors
        public FileServer()
        {
            _FileFolder = ApplicationData.Current.LocalFolder;
            _FileName = "Data.txt";
        }
        #endregion

        #region Methods
       
 
        public async void ReadFile(StorageFolder Folder, String Name)
        {
            string FileText = string.Empty;

            try
            {
                StorageFile InFile = await Folder.GetFileAsync(Name);
            }
            catch
            {

            }

            //return FileText;
        }
        #endregion
    }
}
