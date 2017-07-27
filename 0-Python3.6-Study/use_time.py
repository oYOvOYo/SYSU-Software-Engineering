"""How to use time
"""

import time

print("About time")
print("time.time()                   {}".format(
    time.time()))
print("time.mktime(time.localtime()) {}".format(
    time.mktime(time.localtime())))
print("time.gmtime()                 {}".format(
    time.gmtime()))
print("time.localtime()              {}".format(
    time.localtime()))
print("now time is {time}.".format(
    time=time.asctime(time.localtime())))
print("now time is {time}.".format(
    time=time.strftime("%y/%m/%d %H:%M:%S", time.localtime())))
print("use strptime to back to struct time")
