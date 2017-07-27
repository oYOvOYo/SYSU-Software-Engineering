import math as math

def nsqrt(x):
    # return math.trunc(math.sqrt(x))
    left, right = (0, x)
    ans = (left + right) // 2
    while not (ans * ans <= x and (ans + 1) * (ans + 1) > x):
        # print(ans, ans* "!")
        if ans * ans > x :
            right = ans 
        else:
            left = ans
        ans = (left + right) // 2
    return ans

print(nsqrt(11), nsqrt(1369))