#!/usr/bin/env python
# -*- coding: utf-8 -*-

from  sys import argv # for argv
import string # for string.punctuation string.lstrip() string.rstrip()
class text_statistics(object):
    def main_fuc(self, file_adress):
        """
        main_fuc(self, file_adress)
        主函数
        """
        with open(file_adress,'r') as f:
            self.date = f.read()
        
        special_char = '/-\'' # 不能删除的特殊字符
        delete_char =  (string.punctuation + string.digits).translate(None, special_char) # 需要删除的字符
        self.date = "".join(map(lambda x : x in delete_char and ' ' or x , self.date))   # 删除字符
        self.word_list = self.date.split() # 切片
        self.word_list = map(lambda x : string.rstrip(string.lstrip(x,special_char), 
            special_char), self.word_list) # 删除开头结尾的独立存在的特殊字符
        self.answer = {} # 为了方便先用dict存
        for x in self.word_list:
            if not x in self.answer:
                self.answer[x] = 1
            else:
                self.answer[x] += 1
        self.answer = sorted(self.answer.iteritems(), key= lambda x: x[0].upper()) # 无关大小写的字典序排序
        self.answer = sorted(self.answer, key = lambda x: x[1], reverse = True) # 出现次数排序
        self.answer = filter(lambda x: not x[0] in special_char, self.answer) # 删除单个存在的特殊字符
        
        
        print "%-30s %-10s" % ("world", "number")
        for x in self.answer:
            print "%-30s %-10d" % (x[0], x[1])

    def print_usage(self):
        """
        print_usage()
        展示正确用法
        """
        print """\
Usage: ./text_statistics.py <file>
file :file name and adress\
"""

if __name__ == "__main__":
    analysis = text_statistics()
    if len(argv) != 2:
        analysis.print_usage()
    else:
        analysis.main_fuc(argv[1])

    
    