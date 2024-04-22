#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "sloppy-counter.c"
#include <x86intrin.h>

typedef struct
{
    counter_t *counter;
    int threadID;
    int threshold;
    int operations;
} args;

void *thread_func(void *arg)
{
    args * arguments = (args *) arg;
    counter_t *counter = arguments->counter;
    init(counter, arguments->threshold);
    int max = arguments->operations;
    unsigned long long start = __rdtsc();
    for (int i = 0; i < max; ++i)
    {
        if (i % 3 == 0)
            update(counter, arguments->threadID, 10);
        else
            get(counter);
    }
    unsigned long long end = __rdtsc();
    printf("ticks for %d operations: ", max);
    printf("%llu\n", end - start);
    return NULL;
}

int main(int argc, char *argv[])
{
    int n_threads = atoi(argv[1]);
    int threshold = atoi(argv[2]);
    counter_t counter;
    init(&counter, threshold);
    pthread_t threads[n_threads];
    args args[n_threads];
    int operations = 1000000; //10^6
    for (int i =0; i < n_threads; ++i)
    {
        args[i].counter = &counter;
        args[i].threadID = i;
        args[i].threshold = threshold;
        args[i].operations = operations;
        pthread_create(&threads[i], NULL, thread_func, (void *) &args[i]);
    }
    
    unsigned long long start = __rdtsc();
    for (int i =0; i < n_threads; ++i)
        pthread_join(threads[i], NULL);
    
    unsigned long long end = __rdtsc();
    printf("average ticks for each thread: %llu\n", (end - start) / n_threads);
    return 0;
}