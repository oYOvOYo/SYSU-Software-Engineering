#!/usr/bin/env python
# -*- coding: utf-8 -*-

class TextExercise(object):
    # __init__(self, file_date, exercise_raw = 2)
    # 初始化构造函数
    # file_date：文件数据
    # exercise_raw：每次练习行数
    def __init__(self, file_date, exercise_raw = 2):
        self.file_date_ = file_date
        self.exercise_raw_ = exercise_raw
        self.file_lenth_ = len(file_date)
        self.score_ = 0
        self.MainFuc()
    
    # MainFuc(self)
    # 主函数
    def MainFuc(self):
        self.ShowScore()
    
    # Exercise(self)
    # 练习部分
    def Exercise(self):
        pass
    
    # ShowScore(self)
    # 展示得分部分
    def ShowScore(self):
        print self.file_date_
    