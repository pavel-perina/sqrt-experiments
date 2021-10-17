#!/usr/bin/python3

# apt install python3-pandas python3-seaborn

import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import csv

csv_headers=["Compiler", "Function", "Time[ms]"]
df=pd.read_csv("results.csv", names=csv_headers)

fig, axes = plt.subplots(2, 1, sharex=True, figsize=(12.8, 4.8))
fig.subplots_adjust(right=0.8)



g = sns.stripplot(ax=axes[0], data=df, y="Compiler", x="Time[ms]", hue="Function", alpha=1.0, palette=sns.color_palette("husl",7))
g.legend(bbox_to_anchor=(1.02, 1), borderaxespad=0, title="Function", frameon=False)
#g.figure.set_figheight(5.4)
#g.figure.set_figwidth(9.6)


g = sns.stripplot(ax=axes[1], data=df, y="Function", x="Time[ms]", hue="Compiler", alpha=1.0, palette="Paired")
g.legend(bbox_to_anchor= (1.02,1), borderaxespad=0, title="Compiler", frameon=False)

fig.savefig("results.png")