#!/usr/bin/env python
# -*- coding: utf-8 -*-


from controller import *


class Agenda_UI(object):
    def __init__(self):
        self.controller = AgendaService()
        self.choice = ""
        self.name = ""
        self.password = ""
        self.main_func()

    def main_func(self):
        while not self.choice == 'q':
            print "{:-^54}".format("Agenda")
            print "{:<54}".format("Action")
            self.print_line("l", "log in Agenda by user name and passworld")
            self.print_line("r", "register an Agenda account")
            self.print_line("q", "quit Agenda")
            
            self.choice = raw_input("Agenda : ~$ ")

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
            
            self.choice = raw_input("Agenda " + self.name + " : # ")

    def user_login(self):
        input_data = raw_input("[login in] [user name] [password]")
        input_data = input_data.split("[login in] ")
        if self.controller.user_login(input_data[0], input_data[1]):
            self.name = input_data[0]
            print  "success!"
        else:
            print "login in fail!"
            return 
        self.show_menu()
        self.choice = raw_input("Agenda " + self.name + " : # ")

    def user_register(self):
        print("[register] [user name] [password] [email] [phone]")
        input_data = raw_input("[register] ")
        input_data = input_data.split()
        if self.controller.user_register(input_data[0], input_data[1], input_data[2], input_data[3]):
            print  "success!"
        else:
            print "register fail!"

    def quit_agenda(self):
        print "thanks for using Agenda"

    def user_logout(self):
        print ""

    def delete_user(self):
        print "[delete agenda account]",
        if self.controller.delete_user(self.name, self.password):
            print "success"
        else:
            print "fail to delete Agenda account!"

    def list_all_users(self):
        print "[list all user]"
        print "{0:<15}{1:<25}{2:<15}".format("name","email", "phone")
        for user in self.controller.list_all_users():
            print "{0:<15}{1:<25}{2:<15}".format(user.name, user.email, user.phone)

    def create_meeting(self):
        print "[create meeting] [the number of participators]"
        input_data = raw_input("[create meeting] ")
        participators = ""
        for i in range(int(input_data)):
            print "[create meeting] [please enter the participator", i ,"]"
            participators += raw_input("[create meeting] ")

        print "[create meeting] [title][star time(yyyy-mm-dd/hh:mm)][end time(yyyy-mm-dd/hh:mm)]"
        input_data = raw_input("[create meeting] ")
        input_data = input_data.split()

        print "[create meeting] ",
        if self.controller.create_meeting(self.name, input_data[0], 
            input_data[1], input_data[2], participators):
            print "success!"
        else:
            print "error!"

    def list_all_meetings(self):
        print "[list all sponsor meetings]"
        self.print_meetings(self.controller.list_all_meetings(self.name))

    def list_all_sponsor_meetings(self):
        print "[list all sponsor meetings]"
        self.print_meetings(self.controller.list_all_sponsor_meetings(self.name))

    def list_all_participate_meetings(self):
        print "[list all participate meetings]"
        self.print_meetings(self.controller.list_all_participate_meetings(self.name))

    def querry_meeting_by_title(self):
        print "[queryMeeting] [title]"
        input_data = raw_input("[queryMeeting] ")
        self.print_meetings(self.controller.meeting_query_title(self.name, input_data))

    def querry_meeting_by_time_interval(self):
        print "[queryMeeting] [star time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]"
        input_data = raw_input("[queryMeeting] ")
        input_data = input_data.split()
        self.print_meetings(self.controller.meeting_query_time(input_data[0], input_data[1]))

    def delete_meeting_by_title(self):
        print "[delete meeting] [title]"
        input_data = raw_input("[delete meeting]")
        print "[delete meeting]"
        if self.controller.delete_meeting(self.name, input_data):
            print "delete meeting success!"
        else:
            print "delete meeting fail!"

    def delete_all_meetings(self):
        print "[delete meeting] "
        if self.controller.delete_all_meetings(self.name):
            print "delete meeting success!"
        else:
            print "delete meeting fail!"

    def print_meetings(self, meeting_list):
        print "{:<12}{:<12}{:<20}{:<20}{:<20}".format("title", "sponsor", "start time", 
        "end time", "participator")
        participator = ""
        for meeting in meeting_list:
            participator = ""
            for user in meeting.participator:
                partictipator = participator + user.name + " "
            print "{:<12}{:<12}{:<20}{:<20}{:<20}".format(meeting.title, meeting.sponsor, 
                meeting.start_time, meeting.end_time, participator)

    def print_line(self, operation_char, operation_help):
        print "{:<5}- {:<48}".format(operation_char, operation_help)        

            