# -*- coding: utf-8 -*-

def read_date():
    sudoku = []
    for i in range(9):
        str = raw_input()
        temp = []
        for x in str:
            temp.append(int(x))
        sudoku.append(temp)
    return sudoku