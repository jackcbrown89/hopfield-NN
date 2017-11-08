import numpy as np, matplotlib.pyplot as plt

exts = ['_20', '_40', '_60', '_80', '_100']
mat = np.zeros((6, 5))
hamming_distances = []
fracs = [10, 20, 30, 40, 50, 60]
num_mems = [20, 40, 60, 80, 100]
for ext in exts:
    hamming_distances.append(np.loadtxt('hamming_distances/hamming_distances_fracs%s.txt' % ext).tolist())

print(hamming_distances)
for i in range(0, len(fracs)):
    for j in range(0, len(num_mems)):
        print(i, j)
        mat[i][j] = np.mean(hamming_distances[j][i::len(fracs)])

with plt.xkcd():
    plt.matshow(mat)
    plt.xticks(np.arange(5), num_mems)
    plt.xlabel('Number of Memories')
    plt.yticks(np.arange(6), fracs)
    plt.ylabel('Fraction of corrupted bits')
    # plt.title('Hamming Distance')
    plt.colorbar().set_label('Hamming Distance')
    plt.show()
