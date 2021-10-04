#!/usr/bin/python3

import subprocess

table=[("gcc9",    "g++-9"), 
       ("gcc10",   "g++-10"), 
       ("clang10", "clang++-10"), 
       ("clang12", "clang++-12")]

for row in table:
#    print("\033[96mRunning speed test for " + row[0] + ".\033[0m");
    subprocess.run(["./sqrt-" + row[0]])

