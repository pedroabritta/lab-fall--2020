import numpy as np
import sys

phi = sys.argv[1]

name_file = "log_rmsd_"+str(phi)+".dat"

with open(name_file, "r") as f:
    y = np.loadtxt(f)

x = np.arange(2250, 2973, 1.5)

z = np.polyfit(x,y,1)

out = open("diffvsphi.dat", "a")
out.write(phi+"\t"+str(z[1])+"\n")
out.close()
