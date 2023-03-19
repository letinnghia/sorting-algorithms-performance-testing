import sys
sys.path.append("src/generate_data.py")
import pandas as pd
import matplotlib.pyplot as plt
import generate_data as gd
import argparse

# parse arguments
parser = argparse.ArgumentParser()
parser.add_argument("--datasetspath", type=str)
args = parser.parse_args()

# define constant
DATASETS_PATH = args.datasetspath

# get the current test
currTest = gd.listDir(DATASETS_PATH)[-1]

# read the csv file
df = pd.read_csv(f"{DATASETS_PATH}/{currTest}/results/result.csv", index_col=0)

# resize the chart
fig, ax = plt.subplots(figsize=(14, 8))

# plot the line chart
plt.plot(df.iloc[0], label=df.index[0])
plt.plot(df.iloc[1], label=df.index[1])
plt.plot(df.iloc[2], label=df.index[2])
plt.plot(df.iloc[3], label=df.index[3])

# set the title and labels
plt.title("Sorting Algorithms Performance", fontsize=30, fontweight="bold")
plt.xlabel("Test Cases", fontsize=20)
plt.ylabel("Run Time (ms)", fontsize=16)

# show the legend
plt.legend()

# save and show
plt.savefig(f"{DATASETS_PATH}/{currTest}/results/chart.jpg")
plt.show()