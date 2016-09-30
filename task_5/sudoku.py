# -*- coding: utf-8 -*-

class sudoku(object):
    def __init__(self, date):
        self.date = date
    
    def show(self, date):
        for i in date:
            print i
        print '\n' * 2

    def line_check(self, raw):
        """ check every line is OK """
        return  0 in self.date[raw] and True or range(1, 10) == sorted(self.date[raw])
    
    def column_check(self, column):
        """ check every column is OK """
        temp = []
        for x in self.date:
            temp.append(x[column])
        return  0 in temp and True or range(1, 10) == sorted(temp)

    def block_check(self, raw, column):
        """ check every block is OK """
        raw //= 3
        column //= 3
        temp = []
        for x in self.date[3 * column: 3 * (column + 1)]:
            temp.extend(x[3 * raw: 3 * (raw + 1)])
        return  0 in temp and True or range(1, 10) == sorted(temp)
    
    def isvalid(self, raw, column):
        """ check value is valid """
        return self.block_check(raw, column) and self.line_check(raw) and self.column_check(column)
    
    def check_all(self,date):
        self.date = date
        for x in range(0, 9):
            for y in range(0, 9):
                if False == self.isvalid(x,y):
                    return False
        return True

    def solute(self, date, raw, column):
        temp = []
        for x in date:
            temp.append(x[:])
        for x in range(0, 9):
            for y in range(0, 9):
                if temp[x][y] == 0:
                    if [] == self.next_value(temp, x, y):
                        return 
                    print x,y,self.next_value(temp, x, y), "\n"
                    for value in self.next_value(temp, x, y):
                        temp2 = []
                        temp2.extend(date)
                        # self.show(temp2)
                        temp2[x][y] = value
                        self.solute(temp2, x, y)
                elif x == 8 and y == 8:
                    if self.check_all(date):
                        self.show(temp)
        

    def next_value(self, date, raw, column):
        """ return reasonable next value use set and return a list """
        value = date[raw][column]
        temp = set([])
        for x in date:
            temp.add(x[column])
        temp = temp | set(date[raw])
        raw //= 3
        column //= 3
        for x in date[3 * column: 3 * (column + 1)]:
            temp = temp | set(x[3 * raw: 3 * (raw + 1)])

        return sorted(set(range(value + 1, 10)) - temp)
    

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
    # temp = read_date()
    temp = [ [5, 3, 0, 0, 7, 0, 0, 0, 0],
             [6, 0, 0, 1, 9, 5, 0, 0, 0],
             [0, 9, 8, 0, 0, 0, 0, 6, 0],
             [8, 0, 0, 0, 6, 0, 0, 0, 3],
             [4, 0, 0, 8, 0, 3, 0, 0, 1],
             [7, 0, 0, 4, 2, 6, 0, 0, 6],
             [0, 6, 0, 0, 0, 0, 2, 8, 0],
             [0, 0, 0, 4, 1, 9, 0, 0, 5],
             [0, 0, 0, 0, 8, 0, 0, 7, 9]]
    s = sudoku(temp)
    s.solute(temp,0,0)


