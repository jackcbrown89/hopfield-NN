import numpy as np
from numpy.random import randint

lines = open('memories.txt', 'r').readlines()
new_lines = ""
f = open('memories_corrupted.txt', 'w')

for line in lines:
    line = list(line.strip())
    line = np.array(line)
    # for i in range(7, line.shape[0], 10):
    #     line[i] = randint(0, 1)
    # for i in range(8, line.shape[0], 10):
    #     line[i] = randint(0, 1)
    # for i in range(9, line.shape[0], 10):
    #     line[i] = randint(0, 1)
    for x in range(0, line.size):
        bit = line[x]
        if x > 50 and x % 10 >= 5:
            new_lines += str(randint(0, 2))
        else:
            new_lines += bit

    new_lines += '\n'
f.writelines(new_lines[:-1])
f.close()
