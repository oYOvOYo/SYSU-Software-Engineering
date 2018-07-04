#!/usr/bin/env python
# -*- coding: utf-8 -*-

from model import *


class NoteService(object):
    """Service"""

    def __init__(self):
        self.model = NoteStorage()

    def write_data(self):
        self.model.write_data()

    def create_note(self, title, data):
        """return: success or not"""
        if self.model.querry_note(lambda note: note.title == title):
            return False
        else:
            self.model.create_note(Note(title, data))
            return True

    def delete_note(self, title):
        return self.model.delete_note(lambda note: note.title == title)

    def delete_all_note(self):
        return self.model.delete_note(lambda note: True)

    def list_all_note(self):
        return self.model.querry_note(lambda note: True)

    def querry_note_by_title(self, title):
        return self.model.querry_note(lambda note: note.title == title)

    def querry_note_by_keyword(self, keyword):
        return self.model.querry_note(lambda note: keyword in note.data or
                                      keyword in note.title)

    def update_note_title(self, title, new_title):
        querry = lambda note: note.title == title
        update = lambda note: Note(new_title, note.data)
        return self.model.update_note(querry, update)

    def update_note_data(self, title, new_data):
        querry = lambda note: note.title == title
        update = lambda note: Note(note.title, new_data)
        return self.model.update_note(querry, update)
