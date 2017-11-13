import numpy as np, matplotlib.pyplot as plt

exts = ['_20', '_40', '_60', '_80', '_100']
mat = np.zeros((6, 5))
fracs = np.arange(0, 60, 5)
num_mems = np.arange(1, 80)
hamming_distances = np.zeros((len(fracs), len(num_mems)))

lines = open('hamming_distances/hamming_distances_fracs_0-80.txt').readlines()
for i in range(0, hamming_distances.shape[0]):
    for j in range(0, hamming_distances.shape[1]):
        hamming_distances[i][j] = int(lines[i*j].strip())

print(hamming_distances)

with plt.xkcd():
    plt.matshow(hamming_distances)
    plt.xlabel('Number of Memories')
    plt.ylabel('Fraction of corrupted bits')
    # plt.title('Hamming Distance')
    plt.colorbar().set_label('Hamming Distance')
    plt.show()
