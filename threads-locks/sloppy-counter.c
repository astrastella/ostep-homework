#include <pthread.h>
#define MAX_CPU 4

typedef struct __counter_t
{
    int global; // global counter
    pthread_mutex_t glock; // global lock
    int local[MAX_CPU]; // local counters per CPU
    pthread_mutex_t llock[MAX_CPU]; // local locks
    int threshold; // update frequency
} counter_t;

void init(counter_t *counter, int threshold)
{
    counter->threshold = threshold;
    counter->global = 0;
    pthread_mutex_init(&counter->glock, NULL);
    for (int i = 0; i < MAX_CPU; ++i)
    {
        counter->local[i] = 0;
        pthread_mutex_init(&counter->llock[i], NULL);
    }
}

void update(counter_t *counter, int threadID, int amount)
{
    int cpu = threadID % MAX_CPU;
    pthread_mutex_lock(&counter->llock[cpu]);
    counter->local[cpu] += amount;
    if (counter->local[cpu] >= counter->threshold)
    {
        pthread_mutex_lock(&counter->glock);
        counter->global += counter->local[cpu];
        pthread_mutex_unlock(&counter->glock);
        counter->local[cpu] = 0;
    }
    pthread_mutex_unlock(&counter->llock[cpu]);
}

int get(counter_t *counter)
{
    pthread_mutex_lock(&counter->glock);
    int ret = counter->global;
    pthread_mutex_unlock(&counter->glock);
    return ret;
}