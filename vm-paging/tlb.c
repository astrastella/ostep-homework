#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <pthread.h>

// for future: use a shell script and pipelining to return and process float output
int main(int argc, char *argv[])
{
    assert(argc == 4);

    // pin this thread to CPU 0
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask); // Set the CPU affinity to CPU 0

    if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &mask) == -1) {
        perror("sched_setaffinity");
        return 1;
    }

    int num_pages = atoi(argv[1]);
    int num_trials = atoi(argv[2]);
    int quiet = atoi(argv[3]); // 0 for false, 1 for true
    int jump = sysconf(_SC_PAGESIZE)/sizeof(int);

    if (quiet == 0) printf("Page size is %ld bytes \n", sysconf(_SC_PAGESIZE));
    
    int n = num_pages*jump;
    int *arr = calloc(n, sizeof(int));

    // struct timespec resolution;
    // clock_getres(CLOCK_MONOTONIC, &resolution);
    // printf("Clock resolution: %ld nanoseconds \n", resolution.tv_nsec);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int j = 0; j < num_trials; ++j) 
    {
        for (int i = 0; i < n; i += jump)      
            ++arr[i];        
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    long interval = end.tv_nsec-start.tv_nsec;
    if (quiet == 0)
    {
        printf("Time elapsed for %d operations:  %ld nanoseconds \n", num_trials, interval);
        printf("Time elapsed for each operation: %ld \n", interval/num_trials);
    }

    return interval/num_trials;
}