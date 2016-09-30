# -*- coding: utf-8 -*-

from sudoku import *
from nose.tools import *


if __name__ == '__main__':
    temp = [ 5, 3, 0, 0, 7, 0, 0, 0, 0,
             1, 2, 3, 4, 5, 6, 6, 9, 8,
             0, 9, 8, 0, 0, 0, 0, 6, 0,
             8, 0, 0, 0, 6, 0, 0, 0, 3,
             4, 0, 0, 8, 0, 3, 0, 0, 1,
             7, 0, 0, 0, 2, 0, 0, 0, 6,
             0, 6, 0, 0, 0, 0, 2, 8, 0,
             0, 0, 0, 4, 1, 9, 0, 0, 5,
             0, 0, 0, 0, 8, 0, 0, 7, 9]

    s = sudoku(temp)
    assert_equal(s.line_check(0), True)
    assert_equal(s.line_check(8), True)
    assert_equal(s.line_check(9), False)
    assert_equal(s.line_check(17), False)
    assert_equal(s.line_check(18), True)
   
    temp = [ 5, 3, 0, 0, 7, 0, 0, 0, 0,
             1, 2, 3, 4, 5, 6, 6, 9, 8,
             0, 9, 8, 0, 0, 0, 0, 6, 0,
             8, 9, 0, 0, 6, 0, 0, 0, 3,
             4, 9, 0, 8, 0, 3, 0, 0, 1,
             7, 9, 0, 0, 2, 0, 0, 0, 6,
             0, 9, 0, 0, 0, 0, 2, 8, 0,
             0, 9, 0, 4, 1, 9, 0, 0, 5,
             0, 9, 0, 0, 8, 0, 0, 7, 9]
    s = sudoku(temp)
    assert_equal(s.column_check(0), True)
    assert_equal(s.column_check(72), True)
    assert_equal(s.column_check(1), False)
    assert_equal(s.column_check(73), False)
    assert_equal(s.column_check(80), True)


    
    # s = sudoku(temp)
    # assert_equal(s.block_check(6, 8), False)
    # assert_equal(s.block_check(3, 0), True)
    # assert_equal(s.block_check(3, 1), True)
    # assert_equal(s.block_check(5, 2), True)
    # assert_equal(s.isvalid(0, 0), True)


    
# s = sudoku(temp)
# print s.next_value(temp, 0,5)
   
    # def f(a):
    #     b = a 
    #     b[0]+=1
    #     print a, b 

    # a = [2]
    # f(a)
    # print a 

    # def f2(a):
    #     b = []
    #     b.extend(a) 
    #     b[0]+=1
    #     if b[0] > 10:
    #         return 
    #     print a, b
    #     f2(b)
        

    # a2 = [2]
    # f2(a2)
    # print a2 
    


    