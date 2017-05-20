using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MusicGame.Models
{
    public class UserConfig
    {
        public int RoundNumber { get; set; }
        public int EachRoundChoicesNumber { get; set; }
        public bool DifficultyIncreased { get; set; }
        public string FolderPath { get; set; }

        public static int WinScore = 100;
        public static int LoseScore = -40;
        public static Uri WinImageUri = new Uri("ms-appx:///Assets/correct.png");
        public static Uri LoseImageUri = new Uri("ms-appx:///Assets/incorrect.png");
    }
}
