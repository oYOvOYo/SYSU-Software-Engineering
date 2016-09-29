# -*- coding: utf-8 -*-

class sudoku(object):
    def __init__(self, date):
        self.date = date
    
    def show(self):
        for i in self.date:
            print i
    
    def line_check(self, raw):
        """ check every line is OK """
        if 0 in self.date[raw]:
            return True
        else:
            return range(1, 10) == sorted(self.date[raw])
    
    def column_check(self, column):
        """ check every column is OK """
        temp = []
        for x in self.date:
            temp.append(x[column])
        if 0 in temp:
            return True
        else:
            return range(1, 10) == sorted(temp)

    def block_check(self, raw, column):
        """ check every block is OK """
        raw //= 3
        column //= 3
        temp = []
        for x in self.date[3 * column: 3 * (column + 1)]:
            temp.extend(x[3 * raw: 3 * (raw + 1)])
        if 0 in temp:
            return True
        else:
            return range(1, 10) == sorted(temp)
    
    def isvalid(self, raw, column):
        """ check every block is OK """
        return self.block_check(raw, column) and self.line_check(raw) and self.column_check(column)
    
    def solute(self):
        for x in range(10):
            for y in range(10):
                if self.date[x][y] == 0:

    def next(self, raw, column):
        value = self.date[raw][column]
        temp = []
        for x in self.date:
            temp.append(x[column])
        a = set(temp.extend(self.date[raw]))
        for x in range(value + 1, 10):
            if x in a:
                continue
            else 

def read_date():
    sudoku = []
    for i in range(9):
        str = raw_input()
        temp = []
        for x in str:
            temp.append(int(x))
        sudoku.append(temp)
    return sudoku

if __name__ == '__main__':
    temp = read_date()
    s = sudoku(temp)
    s.solute()
    s.show()


