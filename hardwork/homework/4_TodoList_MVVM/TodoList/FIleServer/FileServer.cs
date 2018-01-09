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
       
        // Question Here !!! 

        /*
         * I just konw a little about Async
         * No return Valur and Forbid ref and out 
         *
         * Don't know how to transport value  
         * if just use this.text, maybe in latter it 
         */
 
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
