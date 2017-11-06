import numpy as np

p = ''
r_int = np.random.random_integers(0, 2**10, 1000)
for i in range(0, r_int.shape[0], 10):
    p += ''.join([np.binary_repr(x, 10) for x in r_int[i:i+10]])
    p += '\n'
f = open('memories.txt', 'w')
f.write(p)
f.close()
