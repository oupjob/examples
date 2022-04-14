

a = { 'a': 1, 'b': 2, 'c': 3, 'd':4 }
b = { 'c': 30, 'd': 40, 'e': 50, 'f': 60 }
l = {}

print({k: [a[k], b[k]] for k in a.keys() & b.keys()})
