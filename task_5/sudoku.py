# -*- coding: utf-8 -*-

class sudoku(object):
    def __init__(self, data):
        """
        intial a sudoku
        data : the datas of a sudoku
        dict : a dict about the unkonw data and it's reasonable values    
        """
        self.data = data
        self.dict = {}
        for i in range(len(self.data)):
            if(self.data[i] == 0):
                self.dict[i] = self.next_value(i)
    
    def show(self):
        """ show a sudoku """
        for i in range(len(self.data)):
            if (i+1) % 9 == 0:
                print self.data[i],'\n',
            else:
                print self.data[i],

    def line_check(self, index):
        """ check every line is OK """
        raw = index // 9
        temp = self.data[raw * 9: raw * 9 + 9]
        return  0 in temp and True or range(1, 10) == sorted(temp)
    
    def column_check(self, index):
        """ check every column is OK """
        column = index % 9
        temp =  self.data[column:len(self.data):9]
        return  0 in temp and True or range(1, 10) == sorted(temp)

    def block_check(self, raw, column):
        """ check every block is OK """
        raw //= 3
        column //= 3
        temp = []
        for x in self.data[3 * column: 3 * (column + 1)]:
            temp.extend(x[3 * raw: 3 * (raw + 1)])
        return  0 in temp and True or range(1, 10) == sorted(temp)
    
    def isvalid(self, raw, column):
        """ check value is valid """
        return self.block_check(raw, column) and self.line_check(raw) and self.column_check(column)
    
    def check_all(self,data):
        """ check value is valid """
        self.data = data
        for x in range(0, 9):
            for y in range(0, 9):
                if 0 == self.data(x,y) or False == self.isvalid(x,y):
                    return False
        return True

    def solute(self, data, raw, column):
        temp = []
        for x in data:
            temp.append(x[:])
        for x in range(0, 9):
            for y in range(0, 9):
                if temp[x][y] == 0:
                    next_list = self.next_value(temp, x, y)
                    if [] == next_list:
                        return
                    for value in next_list:
                        temp[x][y] = value
                        print '*' * (x*10 + y),value,next_list, "\n"
                        self.solute(temp, x, y)
                elif x == 8 and y == 8:
                    # if self.check_all(data):
                    self.show(temp)
        

    def next_value(self, index):
        """ return reasonable next value use set and return a list """
        return [0]
        value = data[raw][column]
        temp = set([])
        for x in data:
            temp.add(x[column])  
        temp = temp | set(data[raw])  
        raw //= 3
        column //= 3
        for x in data[3 * raw: 3 * (raw + 1)]:
            temp = temp | set(x[3 * column: 3 * (column + 1)])
        return sorted(set(range(value + 1, 10)) - temp)
    

def read_data():
    sudoku = []
    for i in range(9):
        str = raw_input()
        temp = []
        for x in str:
            temp.append(int(x))
        sudoku.extend(temp)
    return sudoku

if __name__ == '__main__':
    # temp = read_data()
    temp = [ 5, 3, 0, 0, 7, 0, 0, 0, 0,
             6, 0, 0, 1, 9, 5, 0, 0, 0,
             0, 9, 8, 0, 0, 0, 0, 6, 0,
             8, 0, 0, 0, 6, 0, 0, 0, 3,
             4, 0, 0, 8, 0, 3, 0, 0, 1,
             7, 0, 0, 0, 2, 0, 0, 0, 6,
             0, 6, 0, 0, 0, 0, 2, 8, 0,
             0, 0, 0, 4, 1, 9, 0, 0, 5,
             0, 0, 0, 0, 8, 0, 0, 7, 9]
    s = sudoku(temp)
    s.show()


