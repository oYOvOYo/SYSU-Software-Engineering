# -*- coding: utf-8 -*-

sudoku = []
for i in range(9):
    str = raw_input()
    temp = []
    for x in str:
        temp.append(int(x))
    sudoku.append(temp)

for i in sudoku:
    print i

        