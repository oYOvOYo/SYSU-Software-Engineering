"""Learn numpy
"""

import numpy as np

# 使用list初始化
a = np.array(list(range(1, 10, 2)))
# 使用 arange(begin, end, space), [begin, end) 
b = np.arange(1, 10, 2)
# 使用 linespace(begin, end, nums), [begin, end], 指定元素个数
c = np.linspace(1, 2, 3, endpoint=True)
# 使用 logspace创建等比数列
d = np.logspace(1, 3, 3, base=2, endpoint=True)
# 使用 string
f = np.fromstring("abcdef", dtype=np.int8)
# 使用 func, 第二个参数是shape
g = np.fromfunction(abs, (10, ))


print("a = {}".format(a))
print("b = {}".format(b))
print("c = {}".format(c))
print("d = {}".format(d))
print("f = {}".format(f))
print("g = {}".format(g))

a = np.array([1, 2])
b = np.array([[1], [2]])
print("a + a = {}".format(a + a))
print("a - a = {}".format(a - a))
print("a * 2 = {}".format(a * a))
print("a / 2 = {}".format(a / 2))
print("a * b = {}".format(a * b))
print("a.dot(b) = {}".format(a.dot(b)))