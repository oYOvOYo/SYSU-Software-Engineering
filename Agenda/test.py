#!/usr/bin/env python
# -*- coding: utf-8 -*-


import json


class Date(object):
    def __init__(self, name, score):
        self.name, self.score = name, score

    def print_score(self):
        print "{:>10s} {:>10d}".format(self.name, self.score)


def read_data(dict):
    return Date(dict['name'], dict['score'])

if __name__ == "__main__":
    obj1 = Date("huang", 100)
    obj2 = Date("zhang", 90)
    obj_list = [obj1, obj2]
    print obj_list
    with open('data.json', 'w') as f:
        json.dump(obj_list, f,default=lambda obj: obj.__dict__, indent=2)
        f.close()
    with open('data.json', 'r') as f:
        temp = json.load(f, object_hook=read_data)
        f.close()
    print temp
         