import math

a = 7
b = 23
p = 3571

def fh(m, x, p=p, a=a, b=b):
    return ((a * x + b) % p) % m

def print_fh(m, p, n, x):
    print("log(2, %d) = %d" % (m, math.log(m, 2)))
    for i in range(n):
        x = x + m * p / math.pow(2, i) + 1
        h = fh(m, x)
        print("fh(%d, %d * p/(2 ^ %d) + 1) = %d (x = %d)" % (m, m, i, h, x))

