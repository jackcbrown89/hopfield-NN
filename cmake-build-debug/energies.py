import matplotlib.pyplot as plt
import numpy as np

f = open("energies.txt", "r")
runs = f.readlines()

print(len(runs))
for run in runs:
    plt.plot([float(x) for x in run.split(",")[100:-1][::100]])
plt.title('100 Neuron Energy vs Steps>0 (N=100)')
plt.xlabel('Steps')
plt.ylabel('Energy')
plt.show()
