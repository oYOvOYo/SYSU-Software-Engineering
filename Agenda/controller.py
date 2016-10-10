#!/usr/bin/env python
# -*- coding: utf-8 -*-


from model import *


class AgendaService(object):
    def __init__(self):
        data = Storage()

    def user_login(self, name, password):
        return len(filter(lambda user: name == user.user_data['name']
        and password == user.user_data['password'], data.user_list)) == 1

    def user_register(self, name, password, email, phone):
        if len(filter(lambda user: name == user.user_data['name'], 
        data.user_list)) == 0:
            data.user_list.append(User({'name':name, 'password':password
            'email':email, 'phone':phone}))
            return True
        else:
            return False

    def delete_user()