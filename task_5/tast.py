# -*- coding: utf-8 -*-

from sudoku import *
from nose.tools import *


if __name__ == '__main__':
    temp = [ [0, 0, 0, 4, 5, 6, 7, 8, 9],
             [1, 2, 2, 4, 5, 6, 7, 8, 9],
             [1, 2, 3, 4, 5, 6, 7, 8, 9],
             [1, 2, 3, 4, 5, 6, 7, 8, 9],
             [1, 2, 3, 4, 5, 6, 7, 8, 9],
             [1, 2, 3, 4, 5, 6, 7, 8, 9],
             [1, 2, 3, 4, 5, 6, 7, 8, 9],
             [1, 2, 3, 4, 5, 6, 7, 8, 9],
             [1, 2, 3, 4, 5, 6, 7, 8, 9]]

    s = sudoku(temp)
    assert_equal(s.line_check(0), True)
    assert_equal(s.line_check(1), False)
    assert_equal(s.line_check(2), True)

    temp = [ [0, 1, 1, 4, 5, 6, 7, 8, 9],
             [1, 2, 2, 4, 5, 6, 7, 8, 9],
             [1, 2, 3, 4, 5, 6, 7, 8, 9],
             [1, 2, 4, 4, 5, 6, 7, 8, 9],
             [1, 2, 5, 4, 5, 6, 7, 8, 9],
             [1, 2, 6, 4, 5, 6, 7, 8, 9],
             [1, 2, 7, 4, 5, 6, 7, 8, 9],
             [1, 2, 8, 4, 5, 6, 7, 8, 9],
             [1, 2, 9, 4, 5, 6, 7, 8, 9]]
    s = sudoku(temp)
    assert_equal(s.column_check(0), True)
    assert_equal(s.column_check(1), False)
    assert_equal(s.column_check(2), True)


    temp = [ [0, 1, 1, 4, 5, 6, 7, 8, 9],
             [1, 2, 2, 1, 2, 3, 7, 8, 9],
             [1, 2, 3, 7, 8, 9, 7, 8, 9],
             [1, 2, 4, 4, 5, 6, 7, 8, 9],
             [1, 2, 5, 4, 5, 6, 7, 8, 9],
             [1, 2, 6, 4, 5, 6, 7, 8, 9],
             [1, 2, 7, 4, 5, 6, 7, 8, 9],
             [1, 2, 8, 4, 5, 6, 7, 8, 9],
             [1, 2, 9, 4, 5, 6, 7, 8, 9]]
    s = sudoku(temp)
    assert_equal(s.block_check(6, 8), False)
    assert_equal(s.block_check(3, 0), True)
    assert_equal(s.block_check(3, 1), True)
    assert_equal(s.block_check(5, 2), True)
    assert_equal(s.isvalid(0, 0), True)

    