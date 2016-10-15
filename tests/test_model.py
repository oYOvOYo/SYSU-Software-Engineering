#!/usr/bin/env python
# -*- coding: utf-8 -*-


import unittest
import random
from os import sys, path
sys.path.append(path.dirname(path.dirname(path.abspath(__file__))))
from Agenda.model import *


class TestModelFunctions(unittest.TestCase):
    def test_User(self):
         user = User("Jskyzero", 'hahaha', 'jskyzero@outlook.com', '4673110')
         self.assertEqual(user.name, "Jskyzero")
         self.assertEqual(user.password, "hahaha")
         self.assertEqual(user.email, "jskyzero@outlook.com")
         self.assertEqual(user.phone, "4673110")

    def test_read_user(self):
        user_dic = User("Jskyzero", 'hahaha', 'jskyzero@outlook.com', 
            '4673110').__dict__
        user = read_user(user_dic)
        self.assertEqual(user.name, "Jskyzero")
        self.assertEqual(user.password, "hahaha")
        self.assertEqual(user.email, "jskyzero@outlook.com")
        self.assertEqual(user.phone, "4673110")

    def test_Meeting(self):
        user1 = User("Jskyzero", 'hahaha', 'jskyzero@outlook.com', '4673110')
        user2 = User("Nishiki", "hahaha", "Nishiki2016@outlook.com", "4573110")
        meeting1 = Meeting(user1.name, [user2.name], "2016-08-20/08:30", 
            "2016-08-20/14:20", "meeting1")
        self.assertEqual(meeting1.sponsor, user1.name)
        self.assertEqual(meeting1.start_time, "2016-08-20/08:30")
        self.assertEqual(meeting1.end_time, "2016-08-20/14:20")
        self.assertEqual(meeting1.title, "meeting1")
        self.assertEqual(meeting1.participator, [user2.name])

        self.assertTrue(meeting1.is_participator(user2.name))
        self.assertFalse(meeting1.is_participator(user1.name))

    def test_read_meeting(self):
        user1 = User("Jskyzero", 'hahaha', 'jskyzero@outlook.com', '4673110')
        user2 = User("Nishiki", "hahaha", "Nishiki2016@outlook.com", "4573110")
        meeting_dic = Meeting(user1.name, [user2.name], "2016-08-20/08:30", 
            "2016-08-20/14:20", "meeting1").__dict__
        meeting1 = read_meeting(meeting_dic)
        self.assertEqual(meeting1.sponsor, user1.name)
        self.assertEqual(meeting1.start_time, "2016-08-20/08:30")
        self.assertEqual(meeting1.end_time, "2016-08-20/14:20")
        self.assertEqual(meeting1.title, "meeting1")
        self.assertEqual(meeting1.participator, [user2.name])

    def test_str2time(self):
        start_time = time.mktime(time.strptime("1970-01-01/00:00",
            "%Y-%m-%d/%H:%M"))
        end_time = time.mktime(time.strptime("4000-12-31/23:59",
            "%Y-%m-%d/%H:%M"))
        
        for index in range(10000):
            random.seed(index)
            time0 = time.gmtime(random.uniform(start_time, end_time))
            self.assertEqual(str2time(time.strftime("%Y-%m-%d/%H:%M", time0))[:5],
                time0[:5])

    def test_Storage(self):
        user1 = User("Jskyzero", 'hahaha', 'jskyzero@outlook.com', '4673110')
        user2 = User("Nishiki", "hahaha", "Nishiki2016@outlook.com", "4573110")
        meeting1 = Meeting(user1.name, [user2.name], "2016-08-20/08:30", 
            "2016-08-20/14:20", "meeting1")
        storage = Storage()
        storage.user_list = []
        storage.meeting_list = []
        storage.creat_user(user1)
        storage.creat_user(user2)
        storage.creat_meeting(meeting1)
        self.assertEqual(storage.meeting_list, [meeting1])
        self.assertEqual(len(storage.query_meeting(lambda meeting: True)), 1)
        self.assertEqual(storage.delete_meeting(lambda meeting: True), 1)
        self.assertEqual(len(storage.query_user(lambda user: True)), 2)
        self.assertEqual(storage.delete_user(lambda user: True), 2)


if __name__ == '__main__':
    unittest.main()