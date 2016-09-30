# -*- coding: utf-8 -*-

class sudoku(object):
    def show(self, date):
        for i in date:
            print i
        print '\n' * 2
        
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
                    self.show(temp)
                    exit(-1)
        

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
    date = []
    for i in range(9):
        str = raw_input()
        temp = []
        for x in str:
            temp.append(int(x))
        date.append(temp)
    return date

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
    s = sudoku()
    s.solute(temp,0,0)