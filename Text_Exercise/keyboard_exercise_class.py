#!/usr/bin/env python
# -*- coding: utf-8 -*-

import math # for sqrt()

class TextExercise(object):
    # __init__(self, file_date, exercise_raw = 2)
    # 初始化构造函数
    # file_date：文件数据
    # exercise_raw：每次练习行数
    # line_length: 每行练习字符数
    def __init__(self, file_date, exercise_raw = '2'):
        # 处理非ASCII字符
        file_date = "".join(map(lambda x: ((ord(x) < 32 or ord(x) > 127) and ' ' or x ),file_date)) 
        
        self.file_date_ = file_date
        self.exercise_raw_ = int(exercise_raw)
        self.line_length_ = 40
        self.file_lenth_ = len(file_date)
        self.score_ = 0
        self.total_line_number_ = 0
        self.total_entered_number_ = 0
        self.sigle_line_date_ = ""
        self.MainFuc()
    
    # MainFuc(self)
    # 主函数
    def MainFuc(self):
        self.Exercise()
        self.ShowScores()
    
    # Exercise(self)
    # 练习部分
    def Exercise(self):
        while len(self.file_date_) != 0:
            self.total_line_number_+=1
            if self.total_line_number_ % self.exercise_raw_ == 0:
                if (self.EndExercise()): break

            if len(self.file_date_) < self.line_length_:
                self.sigle_line_date_ = self.file_date_[:]
                self.file_date_ = ""
            else:
                self.sigle_line_date_ = self.file_date_[:self.line_length_]
                self.file_date_ = self.file_date_[self.line_length_:]
            self.ShowLineDate()
            self.UpdateScores(self.ReadLineInport())
            

    # ShowLineDate(self)
    # 展示一行数据      
    def ShowLineDate(self):
        print "$ %05d $" % self.total_line_number_ , ">|", self.sigle_line_date_, "|<"

    # ReadLineInport(self)
    # 读入一行输入
    def ReadLineInport(self):
        print "$ ENTER $", ">|",
        return raw_input()

    # UpdateScores(self)
    # 更新得分数据    
    def UpdateScores(self, LineInput):
        for i in range(min(len(LineInput), self.line_length_)):
            self.total_entered_number_+=1
            if  self.sigle_line_date_[i] == LineInput[i]:
                self.score_+=1
    
    # EndExercise(self)
    # 中途停止练习
    def EndExercise(self):
        print "Do you want to end exercise? y/n",
        return raw_input() == 'y'

    # ShowScore(self)
    # 展示得分部分
    def ShowScores(self):
        correct_rate = self.score_ / float(self.line_length_ * (self.total_line_number_ - 1))
        print "$ %05d $"  % 0, ">|", '-' * self.line_length_, "|<"
        print "\tFile Length:", "%d" %self.file_lenth_
        print "\tTOTAL Correct Character:" , "%d" %self.score_
        print "\tTOTAL Entered Character:" , "%d" %self.total_entered_number_
        print "\tTOTAL Correct Rate", "%.5f" %correct_rate
        print "Your Scores:", "%.0f" % (math.sqrt(correct_rate) * 100)
        print "$ %05d $"  % 0, ">|", '-' * self.line_length_, "|<"
    