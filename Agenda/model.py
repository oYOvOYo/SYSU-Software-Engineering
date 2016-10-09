#!/usr/bin/env python
# -*- coding: utf-8 -*-

# 储存时间
import time

class User(object):
    def __init__(self, user_dict):
        self.user_dict = user_dict

class Meeting(object):
    def __init__(self, meeting_dict):
        self.meeting_dict = meeting_dict

class Storage(object):
    def __init__(self):
        self.read