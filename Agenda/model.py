#!/usr/bin/env python
# -*- coding: utf-8 -*-


import time
import json


class User(object):
    def __init__(self, user_data):
        self.user_data = user_data

class Meeting(object):
    def __init__(self, meeting_data):
        self.meeting_data = meeting_data

class Storage(object):
    def __init__(self):
        self.user_list = []
        self.meeting_list = []
        try :
            with open("../json/user.json",'r') as f:
                self.user_list = json.load(f, object_hook=lambda dic: User(dic))
        except IOError:
            pass
        except ValueError:
            pass

        try :
            with open("../json/meeting.json",'r') as f:
                self.meeting_list = json.load(f, object_hook=lambda dic: Meeting(dic))
        except IOError:
            pass
        except ValueError:
            pass
        


    def write_to_file(self):
        with open("../json/user.json",'w') as f:
            json.dump(self.user_list, f, default=lambda obj: obj.user_data, indent=2)
        with open("../json/meeting.json",'w') as f:
            json.dump(self.meeting_list, f, default=lambda obj: obj.meeting_data, indent=2)

if __name__ == "__main__":
    temp = Storage()
    a = User({'name':'huang', 'list':[123,234], 'data':{1:2}})
    b = Meeting({'name':'huang', 'list':[123,234], 'data':{1:2}})
    print a.user_data
    temp.user_list.append(a)
    temp.meeting_list.append(b)
   
    temp.write_to_file()






