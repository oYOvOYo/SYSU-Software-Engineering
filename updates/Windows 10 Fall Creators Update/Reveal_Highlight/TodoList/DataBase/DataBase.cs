using SQLitePCL;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TodoList.DataBase
{
    class DataBase
    {
        private SQLiteConnection conn;

        public DataBase()
        {
            conn = SQLitePrepare.GetConnetion();
        }

        public void add(Models.TodoClass Todo)
        {
            string sql = @"INSERT INTO TodoList (Id, Title, Details, DueDate, IsComplete, ImageUri)
                                       Values (?, ?, ?, ?, ?, ?)";
            using (var statement = conn.Prepare(sql))
            {
                statement.Bind(1, Todo.Id);
                statement.Bind(2, Todo.Title);
                statement.Bind(3, Todo.Details);
                statement.Bind(4, Todo.DueDate.ToString("yyyy-MM-dd HH:mm:ss"));
                statement.Bind(5, Todo.IsComplete ? 1 : 0);
                statement.Bind(6, Todo.ImageUri == null ? "" : Todo.ImageUri.ToString());
                statement.Step();
            }

        }

        public void delete(Models.TodoClass Todo)
        {
            string sql = @"DELETE FROM TodoList
                           WHERE Id = ?";
            using (var statement = conn.Prepare(sql))
            {
                statement.Bind(1, Todo.Id);
                statement.Step();
            }
        }

        public void update(string Id, Models.TodoClass Todo)
        {
            string sql = @"UPDATE TodoList
                           SET Id = ?, Title = ?, Details = ?, DueDate = ?, IsComplete = ?, ImageUri = ?
                           WHERE Id = ?";
            using (var statement = conn.Prepare(sql))
            {
                statement.Bind(1, Todo.Id);
                statement.Bind(2, Todo.Title);
                statement.Bind(3, Todo.Details);
                statement.Bind(4, Todo.DueDate.ToString("yyyy-MM-dd HH:mm:ss"));
                statement.Bind(5, Todo.IsComplete ? 1 : 0);
                statement.Bind(6, Todo.ImageUri == null ? "" : Todo.ImageUri.ToString());
                statement.Bind(7, Id);
                statement.Step();
            }

        }

        public ObservableCollection<ViewModel.TodoViewModel> select(string str)
        {
            ObservableCollection<ViewModel.TodoViewModel> TodoCollection =
                new ObservableCollection<ViewModel.TodoViewModel>();
            string sql = @"SELECT * FROM TodoList";
            using (var statement = conn.Prepare(sql))
            {
                while (statement.Step() == SQLiteResult.ROW)
                {
                    Models.TodoClass Todo = new Models.TodoClass();
                    Todo.Id = (string)statement[0];
                    Todo.Title = (string)statement[1];
                    Todo.Details = (string)statement[2];
                    Todo.DueDate = DateTime.Parse((string)statement[3]);
                    Todo.IsComplete = (Int64)statement[4] == 1;
                    Todo.ImageUri = ((string)statement[5]).Equals("") ? null : new Uri((string)statement[5]);
                    ViewModel.TodoViewModel NewTodo = new ViewModel.TodoViewModel { Todo = Todo };
                    if (NewTodo.ContainStr(str))
                        TodoCollection.Add(NewTodo);
                }
            }
            return TodoCollection;
        }

        public ObservableCollection<ViewModel.TodoViewModel> select()
        {
            ObservableCollection<ViewModel.TodoViewModel> TodoCollection =
                new ObservableCollection<ViewModel.TodoViewModel>();
            string sql = @"SELECT * FROM TodoList";
            using (var statement = conn.Prepare(sql))
            {
                while (statement.Step() == SQLiteResult.ROW)
                {
                    Models.TodoClass Todo = new Models.TodoClass();
                    Todo.Id = (string)statement[0];
                    Todo.Title = (string)statement[1];
                    Todo.Details = (string)statement[2];
                    Todo.DueDate = DateTime.Parse((string)statement[3]);
                    Todo.IsComplete = (Int64)statement[4] == 1;
                    Todo.ImageUri = ((string)statement[5]).Equals("") ? null : new Uri((string)statement[5]);
                    TodoCollection.Add(new ViewModel.TodoViewModel { Todo = Todo });
                }
            }
            return TodoCollection;
        }
    }
}
