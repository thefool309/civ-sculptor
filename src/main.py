import numpy as np 
import matplotlib.pyplot as plt 
import seaborn as sns 


import sys
import os

script_dir = os.path.dirname(os.path.abspath(__file__))
build_dir = os.path.join(script_dir, "..", "build", "Debug")
build_dir = os.path.abspath(build_dir)

sys.path.append(build_dir)

import civ_module

def main():
    a = 2
    b = 2
    print("Getting a deeper understanding of machine learning and data visualization")
    print("the result of our c++ function is", civ_module.add(a, b))
    print("managed to build c++ function that runs in python")

if __name__ == "__main__":
    main()