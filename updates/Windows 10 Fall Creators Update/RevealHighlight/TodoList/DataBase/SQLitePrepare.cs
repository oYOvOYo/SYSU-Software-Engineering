using SQLitePCL;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TodoList.DataBase
{
    class SQLitePrepare
    {
        public static SQLiteConnection conn;

        public static SQLiteConnection GetConnetion()
        {
            conn = new SQLiteConnection("TodoList.db");

            string sql = @"CREATE TABLE IF NOT EXISTS
                                TodoList (Id          VARCHAR( 36 ) PRIMARY KEY NOT NULL,
                                          Title       VARCHAR( 140 ),
                                          Details     VARCHAR( 140 ),
                                          DueDate     DATETIME,
                                          IsComplete  BOOLEAN,
                                          ImageUri    VAECHAR( 140 )
                            )";
            using (var statement = conn.Prepare(sql))
            {
                statement.Step();
            }

            // Turn on Foreign Key constraints
            sql = @"PRAGMA foreign_keys = ON";
            using (var statement = conn.Prepare(sql))
            {
                statement.Step();
            }
            return conn;
        }

    }
}
