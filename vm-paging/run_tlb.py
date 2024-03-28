#!/usr/bin/env python3

import subprocess
import matplotlib.pyplot as plt

def run_tlb():
    num_trials = 100000
    subprocess.run(["gcc", "-O0", "tlb.c", "-o", "tlb"])
    pages = []
    times = []
    for num_pages in range(14):
        n_page = 2**num_pages
        pages.append(n_page)
        times.append(subprocess.run(["./tlb", str(n_page), str(num_trials), "1"]).returncode)
    
    return pages, times

def plot(pages, times):
    plt.scatter(pages, times)
    plt.show()
    plt.savefig("tlb_measurements.pdf")

if __name__ == "__main__":
    pages, times = run_tlb()
    plot(pages, times)