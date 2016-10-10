#!/usr/bin/env python
# -*- coding: utf-8 -*-


from model import *


class AgendaService(object):
    def __init__(self):
        self.data = Storage()

    def user_login(self, name, password):
        return self.data.query_user(lambda user: name == user['name']
        and password == user['password']) == 1

    def user_register(self, name, password, email, phone):
        if self.data.query_user(lambda user: name == user['name']) == 0:
            user = User(name, password, email, phone)
            self.data.creat_user(user)
            return True
        else:
            return False

    def delete_user(self, name, password):
        if self.data.delete_user(lambda user: name == user.name and 
            password == user.password) > 0:
            self.delete_all_meetings(name)
            for meeting in self.list_all_meetings(name):
                self.delete_meeting(name, meeting.title)
            return True
        return False

    def list_all_users(self):
        return self.data.query_user(lambda x: True)

    def create_meeting(self, name, title, start_date, end_date, participator):
        try:
            str2time
            a = str2time(start_date, "%Y-%m-%d/%H:%M")
            b = str2time(end_date, "%Y-%m-%d/%H:%M")
        except ValueError:
            return False
        if a >= b:
            return False
        for user in participator:
            if user.name == name:
                return False

    def meeting_query(self, name, start_date, end_date):
        try:
            a = str2time(start_date, "%Y-%m-%d/%H:%M")
            b = str2time(end_date, "%Y-%m-%d/%H:%M")
        except ValueError:
            return []

        return self.data.query_meeting(lambda meeting:
        (meeting.sponsor == name or meeting.is_participator(name)) and 
        (str2time(meeting.start_time) and (str2time(meeting.end_time)))or 
        ())

    def list_all_meetings(self, name):
        return self.data.query_meeting(lambda meeting:
            meeting.name == name or meeting.is_participator(name))
    
    def list_all_sponsor_meetings(self, name):
        return self.data.query_meeting(lambda meeting:
            meeting.name == name)

    def list_all_participate_meetings(self, name):
        return self.data.query_meeting(lambda meeting: meeting.is_participator(name))
    
    def delete_meeting(self, name, title):
        return self.data.delete_meeting(lambda meeting: meeting.sponsor == name and meeting.title == title)

    def delete_all_meetings(self, name):
        pass
