#!/usr/bin/env python
# -*- coding: utf-8 -*-

import random  # for
from sys import argv  # for argv
from keyboard_exercise_class import *  # for class

# PrintUsage()
# 展示正确用法


def PrintUsage():
    print """Usage: ./main.py <file> or [-r]  [-n <num>]
file :file name and adress
-r   :for random Characters
-n   :the every sigle times practice raws, default as 4"""

# ReadAllFile(file_adress)
# 读取地址文件中的所有内容
# file_adress：文件地址


def ReadAllFile(file_adress):
    try:
        f = open(file_adress, 'r')
    except IOError:  # 当文件打开出错
        print "IOError: No such file or directory:", "%r" % file_adress
        exit(-1)
    return f.read()

# GenerateRandomNumber(length = 1000)
# 产生随机字符，同时产生特定频率的特定字符
# length：产生字符串长度


def GenerateRandomNumber(length=1000):
    # ugly one line
    return "".join(map(lambda x: random.randint(0, 16) % 4 == 0 and
                       random.choice([',', '.', '/', ';', '\'', '[', ']']) or chr(random.randint(33, 107)), range(length)))

if __name__ == "__main__":
    if len(argv) == 4:
        if argv[2] != "-n":
            PrintUsage()
        else:
            # 注：采用关键字参数匹配模式，方便后续追加选项
            if argv[1] == "-r":
                play = TextExercise(file_date=GenerateRandomNumber(
                    1000), exercise_raw=argv[3])
            else:
                play = TextExercise(file_date=ReadAllFile(
                    argv[1]), exercise_raw=argv[3])
    elif len(argv) == 2:
        if argv[1] == "-r":
            play = TextExercise(
                file_date=GenerateRandomNumber(1000), exercise_raw=4)
        else:
            play = TextExercise(file_date=ReadAllFile(argv[1]), exercise_raw=4)
    elif len(argv) == 1:
        play = TextExercise(
            file_date=GenerateRandomNumber(1000), exercise_raw=4)
    else:
        PrintUsage()
