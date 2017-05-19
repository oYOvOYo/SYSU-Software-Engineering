using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Windows.Storage;

namespace MusicGame.Models
{
    public class FilesServer
    {
        public async Task<List<StorageFile>> GetAllFiles(string path, string fileType)
        {
            List<StorageFile> files = new List<StorageFile>();

            StorageFolder folder = await StorageFolder.GetFolderFromPathAsync(path);
            await RetrieveFilesInFolders(files, folder, fileType);

            return files;
        }

        private async Task RetrieveFilesInFolders(List<StorageFile> list,
            StorageFolder folder, string fileType)
        {
            foreach (var item in await folder.GetFilesAsync())
            {
                if (item.FileType == fileType)
                {
                    list.Add(item);
                }
            }

            foreach (var subFolder in await folder.GetFoldersAsync())
            {
                await RetrieveFilesInFolders(list, subFolder, fileType);
            }
        }
    }
}
