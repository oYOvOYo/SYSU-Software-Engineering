#!/usr/bin/env python
# -*- coding: utf-8 -*-

from sys import argv  # for argv
from keyboard_exercise_class import *  # for class 

# PrintUsage()
# 展示正确用法
def PrintUsage():
    print """Usage: ./main.py <file> [-n <num>]
-n   :the every sigle times practice raws, default as 2"""

# ReadAllFile(file_adress)
# 读取地址文件中的所有内容
# file_adress：文件地址
def ReadAllFile(file_adress):
    try:
        f = open(file_adress, 'r')
    except IOError: # 当文件打开出错
        print "IOError: No such file or directory:", "%r" % file_adress
        exit(-1)
    return f.read()
      
if __name__ == "__main__":
    if len(argv) == 4:
        if argv[2] != "-n":
            PrintUsage()
        else:
            # 注：采用关键字参数匹配模式，方便后续追加选项
            play = TextExercise(file_date = ReadAllFile(argv[1]), exercise_raw = argv[3])
    elif len(argv) == 2:
        play = TextExercise(file_date = ReadAllFile(argv[1]), exercise_raw = 2)
    else:
        PrintUsage()