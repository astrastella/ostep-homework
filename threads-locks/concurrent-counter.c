#include <pthread.h>

typedef struct __counter_t 
{
    int value;
    pthread_mutex_t lock;
} counter_t;

void init(counter_t *counter)
{
    counter->value = 0;
    pthread_mutex_init(&counter->lock, NULL);
}

void increment(counter_t *counter)
{
    pthread_mutex_lock(&counter->lock);
    counter->value++;
    pthread_mutex_unlock(&counter->lock);
}

void decrement(counter_t *counter)
{
    pthread_mutex_lock(&counter->lock);
    counter->value--;
    pthread_mutex_unlock(&counter->lock);
}

int get(counter_t *counter)
{
    pthread_mutex_lock(&counter->lock);
    int value = counter->value;
    pthread_mutex_unlock(&counter->lock);
    return value;
}