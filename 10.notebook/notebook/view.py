#!/usr/bin/env python
# -*- coding: utf-8 -*-

from controller import *


class NoteBook(object):
    """NoteBook UI"""

    def __init__(self):
        self.controller = NoteService()
        self.choice = ""
        self.menu = ""
        self.main_func()

    def exit_note(self):
        self.controller.write_data()
        return True

    def main_func(self):
        while not self.choice == 'q':
            self.main_menu()
            self.choice = raw_input("NoteBook $ ")
            self.exec_choice()

    def main_menu(self):
        print "{:<56}".format(">NoteBook<")
        self.menu = (
            ('a', 'add Note'),
            ('d', 'delete Note by title'),
            ('da', 'delete all Note'),
            ('la', 'list all Note'),
            ('lt', 'list Note by title'),
            ('lk', 'list Note by keyword'),
            ('et', 'edit Note title'),
            ('ec', 'edit Note content'),
            ('q', 'quit Note')
        )
        for operation_char, operation_help in self.menu:
            self.print_line(operation_char, operation_help)

    def show_help(self, str):
        for operation_char, operation_help in self.menu:
            if operation_char == str:
                return operation_help
        return ""

    def exec_choice(self):
        func_return = self.show_help(self.choice)
        if not func_return:
            print "Pleace check yout input"
            return
        print "[{:}]".format(func_return)
        if self.choice == 'a':
            func_return = self.add_note()
        elif self.choice == 'd':
            func_return = self.delete_note()
        elif self.choice == 'da':
            func_return = self.delete_all_note()
        elif self.choice == 'la':
            func_return = self.list_all_note()
        elif self.choice == 'lt':
            func_return = self.list_note_by_title()
        elif self.choice == 'lk':
            func_return = self.list_note_by_keyword()
        elif self.choice == 'et':
            func_return = self.update_note_title()
        elif self.choice == 'ec':
            func_return = self.update_note_content()
        elif self.choice == 'q':
            func_return = self.exit_note()
        if func_return:
            print "[{:}]\n\n".format("SUCCESS")
        else:
            print "[{:}]\n\n".format("FAILURE")

    def add_note(self):
        title = raw_input("[title] ")
        content = raw_input("[content] ")
        if title and content:
            return self.controller.create_note(title, content)
        else:
            return False

    def delete_note(self):
        title = raw_input("[title] ")
        if title:
            return self.controller.delete_note(title)
        else:
            return False

    def delete_all_note(self):
        return self.controller.delete_all_note()

    def list_all_note(self):
        self.print_notes(self.controller.list_all_note())
        return True

    def list_note_by_title(self):
        title = raw_input("[title] ")
        if title:
            self.print_notes(self.controller.querry_note_by_title(title))
            return True
        else:
            return False

    def list_note_by_keyword(self):
        keyword = raw_input("[keyword] ")
        if keyword:
            self.print_notes(self.controller.querry_note_by_keyword(keyword))
            return True
        else:
            return False

    def update_note_title(self):
        title = raw_input("[Note title] ")
        new_title = raw_input("[new title] ")
        if title and new_title:
            return self.controller.update_note_title(title, new_title)
        else:
            return False

    def update_note_content(self):
        title = raw_input("[Note title] ")
        new_content = raw_input("[new input] ")
        if title and new_content:
            return self.controller.update_note_data(title, new_content)
        else:
            return False

    def print_notes(self, notes):
        if notes:
            for note in notes:
                self.print_note(note)
        else:
            print "[EMPTY]"

    def print_note(self, note):
        print "[TITLE]  : ", note.title
        print "[CONTENT]: ", note.data

    def print_line(self, operation_char, operation_help):
        print "{operation_char:<5}- {operation_help:<48}".format(**vars())
