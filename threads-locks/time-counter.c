#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "concurrent-counter.c"
#include <x86intrin.h>

void *thread_func(void *arg)
{
    counter_t *counter = (counter_t *) arg;
    init(counter);
    int max = 100000000; //10^7   
    unsigned long long start = __rdtsc();
    for (int i = 0; i < max; ++i)
    {
        if (i % 3 == 0)
            increment(counter);
        else
            decrement(counter);
    }
    unsigned long long end = __rdtsc();
    printf("ticks for %d operations: ", max);
    printf("%llu\n", end - start);
}

int main(int argc, char *argv[])
{
    int n_threads = atoi(argv[1]);
    counter_t counter;
    init(&counter);
    pthread_t threads[n_threads];
    for (int i =0; i < n_threads; ++i)
        pthread_create(&threads[i], NULL, thread_func, (void *) &counter);
    for (int i =0; i < n_threads; ++i)
        pthread_join(threads[i], NULL);
    return 0;
}