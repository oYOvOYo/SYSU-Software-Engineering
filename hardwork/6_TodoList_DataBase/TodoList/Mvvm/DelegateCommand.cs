using System;
using System.Windows.Input;

namespace TodoList.Mvvm
{
    /*
     * DelegateCommand Class 
     * Used To let a func in a Class and Can be use in view
     * 
     * Copy from Some Place, It seems That it makes no sense to finished by myself now.
     */

    class DelegateCommand : ICommand
    {
        private Action<object> execute;
        private Func<object, bool> canExecute;

        public event EventHandler CanExecuteChanged;

        public DelegateCommand(Action<object> execute)
        {
            this.execute = execute;
            this.canExecute = (x) => { return true; };
        }

        public DelegateCommand(Action<object> execute, Func<object, bool> canExecute)
        {
            this.execute = execute;
            this.canExecute = canExecute;
        }

        public bool CanExecute(object parameter)
        {
            return canExecute(parameter);
        }

        public void RaiseCanExecuteChanged()
        {
            if (CanExecuteChanged != null)
            {
                CanExecuteChanged(this, EventArgs.Empty);
            }
        }

        public void Execute(object parameter)
        {
            execute(parameter);
        }
    }

    // Initial version Class, Not Use parameter

    //class DelegateCommand : ICommand
    //{
    //    private readonly Action _action;

    //    public DelegateCommand(Action action)
    //    {
    //        _action = action;
    //    }

    //    public void Execute(object parameter)
    //    {
    //        _action();
    //    }

    //    public bool CanExecute(object parameter)
    //    {
    //        return true;
    //    }

    //    public event EventHandler CanExecuteChanged { add { } remove { } }
    //}
}
