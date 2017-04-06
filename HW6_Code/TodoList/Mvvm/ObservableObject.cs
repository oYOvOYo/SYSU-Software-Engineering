using System;
using System.ComponentModel;                                    // for change
using System.Runtime.CompilerServices;                          // for [XXX]

namespace TodoList.Mvvm
{
    /*
     * ObservableObject from InotiftPropertyChanged
     * 
     * A base Class that can notify view when property changed
     * 
     * Add a new Func Set to Call event every time,really useful
     * 
     */

    public class ObservableObject : INotifyPropertyChanged
    {
        // PropertyChanged event.
        public event PropertyChangedEventHandler PropertyChanged;

        // PropertyChanged event triggering method.
        public void RaisePropertyChanged([CallerMemberName]string propertyName = null)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        // Set value and Raise Changed Event
        public void Set<T>(ref T storage, T value, [CallerMemberName()]string propertyName = null)
        {
            if (!object.Equals(storage, value))
            {
                storage = value;
                this.RaisePropertyChanged(propertyName);
            }
        }
    }
}
