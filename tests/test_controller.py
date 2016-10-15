#!/usr/bin/env python
# -*- coding: utf-8 -*-


import unittest
import random
from os import sys, path
sys.path.append(path.dirname(path.dirname(path.abspath(__file__))))
from Agenda.controller import *


class TestControllerFunctions(unittest.TestCase):
    def test_controller(self):
        agendaservice = AgendaService()
        agendaservice.model.user_list = []
        agendaservice.model.meeting_list = []
        # test_user_register
        self.assertTrue(agendaservice.user_register(
            "Jskyzero", "hahaha", "jskyzero@outlook.com", "4673110"))
        self.assertFalse(agendaservice.user_register(
            "Jskyzero", "hahaha", "jskyzero@outlook.com", "4673110"))
        self.assertTrue(agendaservice.user_register(
            "Nishiki", "hahaha", "Nishiki2016@outlook.com", "4673110"))

        # test_user_login:
        self.assertTrue(agendaservice.user_login("Jskyzero", "hahaha"))
        self.assertFalse(agendaservice.user_login("Jskyzero", "hahahaha"))
        self.assertFalse(agendaservice.user_login("Jsky", "hahaha"))

        # test_list_all_users
        self.assertEqual(len(agendaservice.list_all_users()), 2)

        # test_create_meeting
        time1 = "2016-08-20/08:00"
        time2 = "2016-08-20/08:01"
        time3 = "2016-08-20/07:59"
        time4 = "2016-08-20/07:60"
        time5 = "2016-08-20/07:58"
        
        # Wrong time time4
        self.assertFalse(agendaservice.create_meeting("Jskyzero", "meeting1",
            time3, time4, ["Nishiki"]))
        # Wrong time start_time1 >= end_time1
        self.assertFalse(agendaservice.create_meeting("Jskyzero", "meeting1",
            time1, time1, ["Nishiki"]))
        # Wrong participate empty
        self.assertFalse(agendaservice.create_meeting("Jskyzero", "meeting1",
            time1, time2, []))
        # Wrong participate wrong name
        self.assertFalse(agendaservice.create_meeting("Jskyzero", "meeting1",
            time1, time2, ["hahaha"]))
        # Wrong participate sponsor in participate
        self.assertFalse(agendaservice.create_meeting("Jskyzero", "meeting1",
            time1, time2, ["Nishiki", "Jskyzero"]))
        
        # Success
        self.assertTrue(agendaservice.create_meeting("Jskyzero", "meeting1",
            time1, time2, ["Nishiki"]))

        # Wrong name 
        self.assertFalse(agendaservice.create_meeting("Jskyzero", "meeting1",
            time5, time2, ["Nishiki"]))

        # Wrong time 
        self.assertFalse(agendaservice.create_meeting("Jskyzero", "meeting2",
            time1, time2, ["Nishiki"]))
        # Wrong time 
        self.assertFalse(agendaservice.create_meeting("Jskyzero", "meeting2",
            time3, time1, ["Nishiki"]))
        # Wrong time 
        self.assertFalse(agendaservice.create_meeting("Jskyzero", "meeting2",
            time5, time2, ["Nishiki"]))
        
        # ORZ




if __name__ == '__main__':
    unittest.main()