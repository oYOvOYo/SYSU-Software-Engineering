#!/usr/bin/env python
# -*- coding: utf-8 -*-


from controller import *

class Agenda_UI(object):
    def __init__(self):
        self.controller = AgendaService()
        self.choice = ''

    def main_menu(self):
        while not self.choice == 'q':
            print "{:-^54}".format("Agenda")
            print "{:<54}".format("Action")
            