#!/usr/bin/env python
# -*- coding: utf-8 -*-


import unittest
from os import sys, path
sys.path.append(path.dirname(path.dirname(path.abspath(__file__))))
from Agenda.model import *


class TestModelFunctions(unittest.TestCase):

    def test_User(self):
         a = User("Jskyzero",'hahaha','jskyzero@outlook.com','4673110')
         self.assertEqual(a.name, "name")
         self.assertEqual(a.password, "hahaha")
         self.assertEqual(a.email, "jskyzero@outlook.com")
         self.assertEqual(a.phone, "4673110")

if __name__ == '__main__':
    unittest.main()