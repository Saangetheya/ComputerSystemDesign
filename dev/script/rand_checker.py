import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn import preprocessing

# Read the file
filename_prefix = "./../traces/rand_runmean"
count = 10  # plot graph in 2*5 subplots

fig, axes = plt.subplots(2, 5, figsize=(40, 20))

for i in range(count):
    filename = "{}_{}.txt".format(filename_prefix, i)

    df = pd.read_csv(filename, header=None)
    axes[i // 5, i % 5].set_ylim(0,100)
    axes[i // 5, i % 5].plot(df[0],)

    # annotate the index value as title  in graph
    axes[i // 5, i % 5].set_title("seed {}".format(i+1))

plt.savefig("./../traces/rand_runmean.png")