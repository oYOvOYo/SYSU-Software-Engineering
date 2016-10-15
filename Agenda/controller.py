#!/usr/bin/env python
# -*- coding: utf-8 -*-


from model import *


class AgendaService(object):
    def __init__(self):
        self.data = Storage()

    def user_login(self, name, password):
        """
        user_login(self, name, password)
        检测符合用户名和密码的唯一用户
        """
        return len(self.data.query_user(
            lambda user: name == user.name and password == user.password)) == 1

    def user_register(self, name, password, email, phone):
        """
        user_register(self, name, password, email, phone)
        先检查用户名重复，然后创建用户
        """
        if len(self.data.query_user(lambda user: name == user.name)) == 0:
            user = User(name, password, email, phone)
            self.data.creat_user(user)
            return True
        else:
            return False

    def delete_user(self, name, password):
        """
        delete_user(self, name, password)
        删除用户，返回删除结果
        """
        if self.data.delete_user(lambda user: name == user.name and
                                 password == user.password) > 0:
            self.delete_all_meetings(name)
            for meeting in self.list_all_meetings(name):
                self.delete_meeting(name, meeting.title)
            return True
        return False

    def list_all_users(self):
        """
        list_all_users(self)
        返回所有用户
        """
        return self.data.query_user(lambda x: True)

    def create_meeting(self, name, title, start_time, end_time, participator):
        """
        create_meeting(self, name, title, start_time, end_time, participator)
        创建会议
        """
        try:
            a = str2time(start_time)
            b = str2time(end_time)
        except ValueError:
            return False
        if a >= b:
            return False

        total_name = participator[:]
        total_name.append(name)

        for user_name in total_name:
            if not self.data.query_user(lambda user:
                    user.name == user_name):
                return False

        if not len(set(total_name)) == len(total_name):
            return False
        
        if self.data.query_meeting(lambda meeting:
                meeting.title == title):
            return False

        
        for user_name in total_name:
            if self.meeting_query_time(user_name, start_time, end_time):
                print user_name, self.meeting_query_time(user_name, start_time, end_time)
                return False
 
        self.data.creat_meeting(Meeting(name, participator,
                                        start_time, end_time, title))
        return True

    def meeting_query_title(self, name, title):
        """
        meeting_query_title(self, name, title)
        根据标题查询会议
        """
        return self.data.query_meeting(lambda meeting:
                                       (meeting.sponsor == name or
                                        meeting.is_participator(name)) and
                                       meeting.title == title)

    def meeting_query_time(self, name, start_time, end_time):
        """
        meeting_query_time(self, name, start_time, end_time)
        根据时间查询会议
        """
        try:
            a = str2time(start_time)
            b = str2time(end_time)
        except ValueError:
            return []
        return self.data.query_meeting(lambda meeting:
                                       ((meeting.sponsor == name or
                                        meeting.is_participator(name)) and
                                       ((str2time(meeting.start_time) <= a and
                                        str2time(meeting.end_time) >= a) or
                                        (str2time(meeting.start_time) <= b and
                                         str2time(meeting.end_time) >= b) or
                                        (str2time(meeting.start_time) >= a and
                                         str2time(meeting.end_time) <= b))))

    def list_all_meetings(self, name):
        """
        list_all_meetings(self, name)
        返回所有会议
        """
        return self.data.query_meeting(lambda meeting:
                                       meeting.sponsor == name or
                                       meeting.is_participator(name))

    def list_all_sponsor_meetings(self, name):
        """
        list_all_sponsor_meetings(self, name)
        返回所有发起的会议
        """
        return self.data.query_meeting(lambda meeting:
                                       meeting.sponsor == name)

    def list_all_participate_meetings(self, name):
        """
        list_all_participate_meetings(self, name)
        返回所有参加的会议
        """
        return self.data.query_meeting(lambda meeting:
                                       meeting.is_participator(name))

    def delete_meeting(self, name, title):
        """
        delete_meeting(self, name, title)
        根据会议标题和发起人删除会议
        """
        return self.data.delete_meeting(lambda meeting:
                                        meeting.sponsor == name and
                                        meeting.title == title)

    def delete_all_meetings(self, name):
        """
        delete_all_meetings(self, name)
        删除全部发起的会议
        """
        return self.data.delete_meeting(lambda meeting:
                                        meeting.sponsor == name)

    def write_to_file(self):
        """
        write_to_file(self)
        写入文件
        """
        self.data.write_to_file()
