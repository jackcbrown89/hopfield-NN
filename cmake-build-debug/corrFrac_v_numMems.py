import numpy as np, matplotlib.pyplot as plt, pandas as pd, seaborn as sns

fracs = np.arange(0, 60, 5)
num_mems = np.arange(1, 80)

lines = open('hamming_distances/hamming_distances_fracs_0-80.txt').readlines()
hamming_distances = np.array([int(x.strip()) for x in lines])
hamming_distances = hamming_distances.reshape((79, 12)).T

df = pd.DataFrame(hamming_distances, index=fracs, columns=num_mems)
sns.heatmap(df)
plt.xlabel('Number of Memories')
plt.ylabel('Fraction of corrupted bits')
plt.title('Hamming Distance')
plt.show()
