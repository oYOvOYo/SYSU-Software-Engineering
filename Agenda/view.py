#!/usr/bin/env python
# -*- coding: utf-8 -*-


from controller import *


class Agenda_UI(object):
    def __init__(self):
        self.controller = AgendaService()
        self.choice = ''
        self.name = ""
        self.main_func()

    def get_choice(self):
        choice = raw_input("Agenda : ~$ ")
        self.choice = choice

    def main_func(self):
        while not self.choice == 'q':
            print "{:-^54}".format("Agenda")
            print "{:<54}".format("Action")
            self.print_line("l", "log in Agenda by user name and passworld")
            self.print_line("r", "register an Agenda account")
            self.print_line("q", "quit Agenda")
            self.get_choice()
            
            if self.choice == 'l':
                self.user_login()
            elif self.choice == 'r':
                self.user_register()
            elif self.choice == 'q':
                self.user_logout()
            else:
                print "please check your inport"

    def show_menu(self):
        print "{:-^54}".format("Agenda")
        print "{:<54}".format("Action")
        self.print_line("o", "log out Agenda")
        self.print_line("dc", "delete Agenda account")
        self.print_line("lu", "list all Agenda user")
        self.print_line("cm", "create a meeting")
        self.print_line("la", "list all meetings")
        self.print_line("las", "list all sponsor meetings")
        self.print_line("lap", "list all participate meetings")
        self.print_line("qm", "querry meetings by title")
        self.print_line("qt", "querry meeting by time interval")
        self.print_line("dm", "delete meeting by title")
        self.print_line("da", "delete all meetings")
        print "{:-^54}".format("")
        

    def excute_operation(self):
        while not self.choice == "0":
            if self.choice == "dc":
                self.delete_user()
            elif self.choicce == "lu":
                self.list_all_users()
            elif self.choice == "cm":
                self.create_meeting()
            elif self.choice == "la":
                self.list_all_meetings()
            elif self.choice == "las":
                self.list_all_sponsor_meetings()
            elif self.choice == "lap":
                self.list_all_participate_meetings()
            elif self.choice == "qm":
                self.querry_meeting_by_title()
            elif self.choice == "qt":
                self.querry_meeting_by_time_interval()
            elif self.choice == "da":
                self.delete_all_meetings()
            else:
                print "Please check your input"
            
            self.choice = raw_input("Agenda", self.name, " : # ")

    def user_login(Self):
        print "[login in] [user name] [password]"
         

    def user_register(self):
        pass

    def quit_agenda(self):
        pass

    def user_logout(self):
        pass

    def delete_user(self):
        pass

    def list_all_users(self):
        pass

    def create_meeting(self):
        pass

    def list_all_meetings(self):
        pass

    def list_all_sponsor_meetings(self):
        pass

    def list_all_participate_meetings(self):
        pass

    def querry_meeting_by_title(self):
        pass

    def querry_meeting_by_time_interval(self):
        pass

    def delete_meeting_by_title(self):
        pass

    def delete_all_meetings(self):
        pass

    def print_meetings(self, meeting):
        pass

    def print_line(self, operation_char, operation_help):
        print "{:<5}- {:<48}".format(operation_char, operation_help)        

            