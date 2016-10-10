#!/usr/bin/env python
# -*- coding: utf-8 -*- 

from sys import argv # for argv
import string # for string.puctuation string.strip()
import os # for os.listdir()

class text_analysis(object):
    def main_fuc(self, file_adress):
        """
        main_fuc(self, file_adress)
        主函数
        """
        special_char = '/-\'' # 不能删除的特殊字符
        delete_char =  (string.punctuation + string.digits).translate(None, special_char) # 需要删除的字符
        self.word_set = None # 共同出现的单词集合
        self.old_dict = None # 上一次的由单词和出现次数组成的dict

        for each_file_adress in file_adress:
            try: # 防止文件无法读入
                with open(each_file_adress, 'rt') as f:
                    self.data = f.read()
            except IOError: # 当文件打开出错
                print "打开文件出错", "%r" % each_file_adress
                exit(-1) 
            
            self.data = "".join(map(lambda x : x in delete_char and ' ' or x , self.data))   # 删除字符
            self.word_list = self.data.split() # 切片
            self.word_list = map(lambda x : string.strip(x,special_char), self.word_list) # 删除开头结尾的独立存在的特殊字符
            self.new_dict = {} # 为了方便先用dict存
            for x in self.word_list:
                if not x in self.new_dict:
                    self.new_dict[x] = 1
                else:
                    self.new_dict[x] += 1

            if self.word_set == None: # 对于第一次处理的文章
                self.word_set = set(map(lambda x: x[0], self.new_dict.iteritems())) # 储存所有单词
                self.ans = self.new_dict # 旧dict就是本身
            else: # 对于第二次及以后的文章，每次求交集
                self.word_set = self.word_set & set(map(lambda x: x[0], self.new_dict.iteritems()))
                self.ans = {} # 对于新单词集合产生结果
                for x in self.word_set:
                    self.ans[x] = self.old_dict[x] + self.new_dict[x]
            # 旧dict更新为每次的结果
            self.old_dict = self.ans
        # 全部处理以后只需要对总结果进行一次排序
        self.ans = sorted(self.ans.iteritems(), key= lambda x: x[0].upper()) # 无关大小写的字典序排序
        self.ans = sorted(self.ans, key = lambda x: x[1], reverse = True) # 出现次数排序
        self.ans = filter(lambda x: not x[0] in special_char, self.ans) # 删除单个存在的特殊字符
        #按照格式输出
        print "%-30s %-10s" % ("world", "number")
        for x in self.ans:
            print "%-30s %-10d" % (x[0], x[1])

    def print_usage(self):
        """
        print_usage()
        展示正确用法
        """
        print """\
Usage: ./text_statistics.py -a | <file> <file> [<file>...]
a    : all doucuments in current directory
file : file name and adress\
"""

if __name__ == "__main__":
    analysis = text_analysis()
    if len(argv) > 2 and argv[1] != '-a': # 传入指定参数
        analysis.main_fuc(argv[1:]) 
    elif len(argv) == 2 and argv[1] == '-a': # 传入当前目录下所有非.py 的文件列表
        analysis.main_fuc(filter(lambda x : not '.py' in x,  os.listdir('.')))
    else:
        analysis.print_usage()
