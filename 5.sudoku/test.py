# -*- coding: utf-8 -*-

from sudoku import *
from nose.tools import *


if __name__ == '__main__':
    # temp = [ 5, 3, 0, 0, 7, 0, 0, 0, 0,
    #          1, 2, 3, 4, 5, 6, 6, 9, 8,
    #          0, 9, 8, 0, 0, 0, 0, 6, 0,
    #          8, 0, 0, 0, 6, 0, 0, 0, 3,
    #          4, 0, 0, 8, 0, 3, 0, 0, 1,
    #          7, 0, 0, 0, 2, 0, 0, 0, 6,
    #          0, 6, 0, 0, 0, 0, 2, 8, 0,
    #          0, 0, 0, 4, 1, 9, 0, 0, 5,
    #          0, 0, 0, 0, 8, 0, 0, 7, 9]

    # s = sudoku(temp)
    # assert_equal(s.line_check(0), True)
    # assert_equal(s.line_check(8), True)
    # assert_equal(s.line_check(9), False)
    # assert_equal(s.line_check(17), False)
    # assert_equal(s.line_check(18), True)
   
    # temp = [ 5, 3, 0, 0, 7, 0, 0, 0, 0,
    #          1, 2, 3, 4, 5, 6, 6, 9, 8,
    #          0, 9, 8, 0, 0, 0, 0, 6, 0,
    #          8, 9, 0, 0, 6, 0, 0, 0, 3,
    #          4, 9, 0, 8, 0, 3, 0, 0, 1,
    #          7, 9, 0, 0, 2, 0, 0, 0, 6,
    #          0, 9, 0, 0, 0, 0, 2, 8, 0,
    #          0, 9, 0, 4, 1, 9, 0, 0, 5,
    #          0, 9, 0, 0, 8, 0, 0, 7, 9]
    # s = sudoku(temp)
    # assert_equal(s.column_check(0), True)
    # assert_equal(s.column_check(72), True)
    # assert_equal(s.column_check(1), False)
    # assert_equal(s.column_check(73), False)
    # assert_equal(s.column_check(80), True)

    # temp = [ 5, 3, 0, 1, 2, 3, 0, 0, 0,
    #          1, 2, 3, 4, 5, 6, 6, 9, 8,
    #          0, 9, 8, 7, 8, 9, 0, 6, 0,
    #          8, 9, 0, 0, 6, 0, 0, 0, 3,
    #          4, 9, 0, 8, 0, 3, 0, 0, 1,
    #          7, 9, 0, 0, 2, 0, 0, 0, 6,
    #          0, 9, 0, 0, 0, 0, 2, 8, 4,
    #          0, 9, 0, 4, 1, 9, 1, 6, 5,
    #          0, 9, 0, 0, 8, 0, 3, 7, 9]
    # s = sudoku(temp)
    # assert_equal(s.block_check(0), True)
    # assert_equal(s.block_check(9), True)
    # assert_equal(s.block_check(10), True)
    # assert_equal(s.block_check(11), True)
    # assert_equal(s.block_check(18), True)
    # assert_equal(s.block_check(19), True)
    # assert_equal(s.block_check(2), True)

    # assert_equal(s.block_check(3), True)
    # assert_equal(s.block_check(5), True)

    # assert_equal(s.block_check(80), True)

    temp = [8,1,2,7,5,3,6,4,9,
        9,4,3,6,8,2,1,7,5,
        6,7,5,4,9,1,2,8,3,
        1,5,4,2,3,7,8,9,6,
        3,6,9,8,4,5,7,2,1,
        2,8,7,1,6,9,5,3,4,
        5,2,1,9,7,4,3,6,8,
        4,3,8,5,2,6,9,1,7,
        7,9,6,3,1,8,4,5,2]

    s = sudoku(temp)
    for x in range(81):
        assert_equal(s.isvalid(x), True)

    temp = [ 5, 3, 0, 1, 2, 3, 0, 0, 0,
             1, 2, 3, 4, 5, 6, 6, 9, 8,
             0, 9, 8, 7, 8, 9, 0, 6, 0,
             8, 9, 0, 0, 6, 0, 0, 0, 3,
             4, 9, 0, 8, 0, 3, 0, 0, 1,
             7, 9, 0, 0, 2, 0, 0, 0, 6,
             0, 9, 0, 0, 0, 0, 2, 8, 4,
             0, 9, 0, 4, 1, 9, 1, 6, 5,
             0, 9, 0, 0, 8, 0, 3, 7, 9]
    s = sudoku(temp)
    assert_equal(s.next_value(0), [9])    


    
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
    

# temp = [ 5, 3, 0, 0, 7, 0, 0, 0, 0,
    #          6, 0, 0, 1, 9, 5, 0, 0, 0,
    #          0, 9, 8, 0, 0, 0, 0, 6, 0,
    #          8, 0, 0, 0, 6, 0, 0, 0, 3,
    #          4, 0, 0, 8, 0, 3, 0, 0, 1,
    #          7, 0, 0, 0, 2, 0, 0, 0, 6,
    #          0, 6, 0, 0, 0, 0, 2, 8, 0,
    #          0, 0, 0, 4, 1, 9, 0, 0, 5,
    #          0, 0, 0, 0, 8, 0, 0, 7, 9]
    