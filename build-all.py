#!/usr/bin/python3

import shutil
import subprocess
import os

table=[("gcc9",    "g++-9"), 
       ("gcc10",   "g++-10"), 
       ("clang10", "clang++-10"), 
       ("clang12", "clang++-12")]

for row in table:
    print("\033[96mCompiling with " + row[0] + ".\033[0m")
    try:
        shutil.rmtree("build-linux")
    except:
        pass

    os.environ["CXX"] = row[1]
    subprocess.run(["cmake", ".", "-Bbuild-linux", "-DCMAKE_BUILD_TYPE=Release"])
    os.chdir("build-linux")
    subprocess.run(["make"])
    os.chdir("..")
    shutil.copyfile("build-linux/src/sqrt", "sqrt-" + row[0])

for row in table:
    print("\033[96mRunning speed test for " + row[0] + ".\033[0m");
    subprocess.run(["./sqrt-" + row[0]])

