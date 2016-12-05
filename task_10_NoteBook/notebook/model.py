#!/usr/bin/env python
#-*- coding:utf-8 -*-


import json


class Note(object):
    """A class to store notes"""

    def __init__(self, title, data):
        self.title, self.data = title, data


def read_Note(dic):
    return Note(dic['title'], dic['data'])


class NoteStorage(object):
    """A class to store all notes"""

    def __init__(self):
        self.note_list = []
        self.read_data()

    def read_data(self):
        try:
            with open("./data/note.json", 'r') as f:
                try:
                    self.note_list = json.load(
                        f, object_hook=lambda dic: read_Note(dic)
                    )
                except ValueError:
                    print "Empty Note Data Before"
        except IOError:
            print "No Data File before"

    def write_data(self):
        with open("./data/note.json", 'w') as f:
            json.dump(self.note_list, f, default=lambda obj: obj.__dict__,
                      indent=2)

    def create_note(self, note):
        self.note_list.append(note)

    def querry_note(self, filter_func):
        return filter(filter_func, self.note_list)

    def update_note(self, filter_func, update_func):
        num = len(filter(filter_func, self.note_list))
        self.note_list = map(lambda note: update_func(
            note) if filter_func(note) else note,  self.note_list)
        return num

    def delete_note(self, filter_func):
        num = len(self.note_list)
        self.note_list = filter(
            lambda note: not filter_func(note), self.note_list)
        return num - len(self.note_list)
