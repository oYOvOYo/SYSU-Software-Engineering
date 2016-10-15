#!/usr/bin/env python
# -*- coding: utf-8 -*-


import time
import json


class User(object):
    """
    User(object)
    """
    def __init__(self, name, password, email, phone):
        self.name, self.password, self.email, self.phone = \
            name, password, email, phone


def read_user(dic):
    """
    read_user(dic)
    将json的dic转成user
    """
    return User(dic['name'], dic['password'], dic['email'], dic['phone'])


class Meeting(object):
    """
    Meeting(object)
    """
    def __init__(self, sponsor, participator, start_time, end_time, title):
        self.sponsor, self.participator, self.start_time, self.end_time, \
            self.title = sponsor, participator, start_time, end_time, title

    def is_participator(self, name):
        """
        is_participator(self, name)
        检查该用户是否是参与者
        """
        return name in self.participator


def read_meeting(dic):
    """
    read_meeting(dic)
    将json的dic转成meeting
    """
    if 'name' in dic:
        return read_user(dic)
    else:
        return Meeting(dic['sponsor'], dic['participator'],
                       dic['start_time'], dic['end_time'], dic['title'])


def str2time(time_str):
    """
    str2time(time_str)
    将字符格式的时间转成时间元组
    """
    return time.strptime(time_str, "%Y-%m-%d/%H:%M")


class Storage(object):
    """
    Storage(object)
    """
    def __init__(self):
        """
        __init__(self)
        从json中读取数据
        """
        self.user_list = []
        self.meeting_list = []
        try:
            with open("./json/user.json", 'r') as f:
                try:
                    self.user_list = json.load(
                        f, object_hook=lambda dic: read_user(dic))
                except ValueError:
                    pass
        except IOError:
            pass

        try:
            with open("./json/meeting.json", 'r') as f:
                try:
                    self.meeting_list = json.load(
                        f, object_hook=lambda dic: read_meeting(dic))
                except ValueError:
                    pass
        except IOError:
            pass

    def write_to_file(self):
        """
        write_to_file(self)
        保存文件
        """
        with open("./json/user.json", 'w') as f:
            json.dump(self.user_list, f, default=lambda obj: obj.__dict__,
                      indent=2)
        with open("./json/meeting.json", 'w') as f:
            json.dump(self.meeting_list, f, default=lambda obj: obj.__dict__,
                      indent=2)

    def creat_user(self, user):
        """
        creat_user(self, user)
        """
        self.user_list.append(user)

    def query_user(self, filter_func):
        """
        query_user(self, filter_func)
        返回符合删选条件的user list
        """
        return filter(filter_func, self.user_list)

    def update_user(self, filter_func, update_func):
        """
        update_user(self, filter_func, update_func)
        将update用于符合条件的user，并返回处理个数
        """
        self.user_list = map(lambda user: update_func(user) if
                             filter_func(user) else user, self.user_list)
        return self.user_list

    def delete_user(self, filter_func):
        """
        delete_user(self, filter_func)
        删除user，返回删除个数
        """
        num = len(filter(filter_func, self.user_list))
        self.user_list = filter(lambda user: not filter_func(user),
                                self.user_list)
        return num

    def creat_meeting(self, meeting):
        """
        creat_meeting(self, meeting)
        创建会议
        """
        self.meeting_list.append(meeting)

    def query_meeting(self, filter_func):
        """
        query_meeting(self, filter_func)
        """
        return filter(filter_func, self.meeting_list)

    def update_meeting(self, filter_func, update_func):
        """
        update_meeting(self, filter_func, update_func)
        """
        self.meeting_list = map(lambda meeting: update_func(meeting)
                                if filter_func(meeting)
                                else meeting, self.meeting_list)
        return self.meeting_list

    def delete_meeting(self, filter_func):
        """
        delete_meeting(self, filter_func)
        """
        num = len(filter(filter_func, self.meeting_list))
        self.meeting_list = filter(lambda meeting: not filter_func(meeting),
                                   self.meeting_list)
        return num
