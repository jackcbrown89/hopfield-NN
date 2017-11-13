import numpy as np

p = ''
r_ints = [np.random.random_integers(0, 2**10, x*10) for x in range(0, 80)]
f = open('memories/memories_0-80.txt', 'w')
for r_int in r_ints:
    for i in range(0, r_int.shape[0], 10):
        p += ''.join([np.binary_repr(x, 10) for x in r_int[i:i+10]])[:100]
        p += '\n'
f.write(p)
f.close()
