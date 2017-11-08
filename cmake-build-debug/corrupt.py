import numpy as np
from numpy.random import random_integers, randint
num_mems = '100'
fracs = [10, 20, 30, 40, 50, 60]
lines = open('memories/memories_%s.txt' % num_mems, 'r').readlines()
new_lines = ""
k_str = ""
f = open('corrupted_memories/memories_corrupted_fracs_%s.txt' % num_mems, 'w')

info = open('corrupted_memory_info/memories_corr_info_fracs_%s.txt' % num_mems, 'w')

for line in lines:
    line = list(line.strip())
    line = np.array(line)
    # num_k = randint(0, line.size)
    for frac in fracs:
        k_indices = random_integers(0, line.size-1, frac)
        k_str += str(frac)
        for x in range(0, line.size):
            if x in k_indices:
                if line[x] == '0':
                    new_lines += '1'

                elif line[x] == '1':
                    new_lines += '0'

            else:
                new_lines += line[x]

        new_lines += '\n'
        k_str += '\n'

f.writelines(new_lines[:-1])
info.writelines(k_str[:-1])
f.close()
info.close()
