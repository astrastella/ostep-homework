#!/usr/bin/env python3

import subprocess
import matplotlib.pyplot as plt

def run_tlb():
    num_trials = 100000
    subprocess.run(["gcc", "-O0", "tlb.c", "-o", "tlb"])
    pages = []
    times = []
    for num_pages in range(16):
        n_page = 2**num_pages
        pages.append(n_page)
        times.append(subprocess.run(["./tlb", str(n_page), str(num_trials), "1"]).returncode)
    
    return pages, times

def plot(pages, times):
    fig, ax = plt.subplots()
    ax.scatter(pages, times)
    ax.set_xscale('log', base=2)
    ax.set_xlabel("Number of pages")
    ax.set_ylabel("Time per access (ns)")
    plt.show()
    plt.savefig("tlb_measurements.pdf")

if __name__ == "__main__":
    pages, times = run_tlb()
    plot(pages, times)