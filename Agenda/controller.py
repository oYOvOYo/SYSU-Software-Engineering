#!/usr/bin/env python
# -*- coding: utf-8 -*-


from model import *


class AgendaService(object):
    def __init__(self):
        self.data = Storage()

    def user_login(self, name, password):
        return len(filter(lambda user: name == user['name']
        and password == user['password'], self.data.user_list)) == 1

    def user_register(self, name, password, email, phone):
        if len(filter(lambda user: name == user['name'], 
        self.data.user_list)) == 0:
            self.data.user_list.append({'name':name, 'password':password
            'email':email, 'phone':phone})
            return True
        else:
            return False

    def delete_user(self, name, password):
        for index, user in enumerate(self.data.user_list[:]):
            if name == user['name'] and password == user['password']:
                self.data.user_list.pop(index)
                self.de
                return True
        return False

    def list_all_users(self):
        return self.data.user_list

    def create_meeting(self, name, title, star_date, end_date, participator):
        pass

    def meeting_query(self, name, star_date, end_date):
        return filter(lambda meeting: time.strptime(meeting['star_date'], "%Y-%m-%d/%H:%M"), self.data.meeting_list)

    def list_all_participate_meetings(self, name):
        return filter(lambda meeting: time.strptime(meeting['star_date'], "%Y-%m-%d/%H:%M"), self.data.meeting_list)

    def delete_meeting(self, name, title):
        pass

    def delete_all_meetings(self, name):
        pass
