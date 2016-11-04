# -*- coding: utf-8 -*-

class sudoku(object):
    def __init__(self, data):
        """
        intial a sudoku
        data : the datas of a sudoku
        list : the indix of all the zero value
        dict : a dict about the unkonw data and it's reasonable values    
        """
        self.data = data
        self.dict = {}
        self.list = []
        for i in range(len(self.data)):
            if(self.data[i] == 0):
                self.list.append(i)
                self.dict[i] = self.next_value(i)
    
    def show(self):
        """ show a sudoku """
        for i in range(len(self.data)):
            if (i+1) % 9 == 0:
                print self.data[i],'\n',
            else:
                print self.data[i],

    def raw(self, index):
        """ Get every line """
        raw = index // 9
        return self.data[raw * 9: raw * 9 + 9]
    
    def column(self, index):
        """ Get every column """
        column = index % 9
        return self.data[column:len(self.data):9]

    def block(self, index):
        """ Get every block """
        raw = index // 9
        column = index % 9
        raw //= 3
        column //= 3
        temp = []
        for x in range(3):
            raw_temp = self.data[(3 * raw + x) * 9: (3 * raw + 1 + x) * 9]
            temp.extend(raw_temp[3 * column: 3 * column + 3])
        return temp
    
    def isvalid(self, index):
        """ check value is valid """
        temp = []
        temp.append(self.raw(index))
        temp.append(self.column(index))
        temp.append(self.block(index))
        ans = True
        for x in temp:
            ans *= 0 in x and True or range(1, 10) == sorted(x)
        return bool(ans)
    
    def check_all(self,data):
        """ check value is valid """
        self.data = data
        for x in range(81):
            if 0 == self.data[x] or False == self.isvalid(x):
                return False
        return True

    def solute(self, index):
        """ solute a sudoku """
        for value in self.dict[index]:
            self.data[index] = value

            if self.isvalid(index):
                if len(self.list) < 1:
                    self.show()
                    exit()
                index2 = self.list.pop()
                self.solute(index2)
                self.data[index2] = 0
                self.list.append(index2)
        

    def next_value(self, index):
        """ return reasonable next value use set and return a list """
        temp = []
        ans = []
        temp.extend(self.raw(index))
        temp.extend(self.column(index))
        temp.extend(self.block(index))
        for x in range(1,10):
            if not(x in temp):
                ans.append(x)
            self.data[index] = 0 
        return ans

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
    temp = read_data()
    # temp = [ 5, 3, 0, 0, 7, 0, 0, 0, 0,
    #          6, 0, 0, 1, 9, 5, 0, 0, 0,
    #          0, 9, 8, 0, 0, 0, 0, 6, 0,
    #          8, 0, 0, 0, 6, 0, 0, 0, 3,
    #          4, 0, 0, 8, 0, 3, 0, 0, 1,
    #          7, 0, 0, 0, 2, 0, 0, 0, 6,
    #          0, 6, 0, 0, 0, 0, 2, 8, 0,
    #          0, 0, 0, 4, 1, 9, 0, 0, 5,
    #          0, 0, 0, 0, 8, 0, 0, 7, 9]
    s = sudoku(temp)
    s.solute(s.list.pop())


