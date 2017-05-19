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
    }
}
