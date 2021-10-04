#!/usr/bin/python3

# apt install python3-pandas python3-seaborn

import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

csv_headers=["Compiler", "Function", "Time[ms]"]
df=pd.read_csv("results.csv", names=csv_headers)
#grp=df.groupby(["Compiler", "Function"]).min()
#grp.unstack("Function").plot.barh()
#plt.savefig("test.png")

sns.catplot(data=df, y="Compiler", x="Time[ms]", hue="Function", height=4.0, aspect=2.0/1.0)
plt.savefig("test.png")
