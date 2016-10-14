#!/usr/bin/env python
# -*- coding: utf-8 -*-

import json # for
class Date(object):
    def __init__(self, name, score, dic):
        self.name, self.score, self.dic = name, score, dic

    def print_score(self):
        print "{:>10s} {:>10d}".format(self.name, self.score), self.dic

def read_data(dic):
    return Date(dic['name'], dic['score'], dic['dic'])
    
if __name__ == "__main__":
    with open('data.json', 'r') as f:
        temp = json.load(f, object_hook=read_data)
        f.close()
    print temp

    obj1 = Date("huang", 100, [1, 2])
    obj2 = Date("zhang", 90, obj1)
    obj_list = temp+[obj1, obj2]
    print obj_list
    with open('data.json', 'w') as f:
        json.dump(obj_list, f,default=lambda obj: obj.__dict__, indent=2)
        f.close()
    
         