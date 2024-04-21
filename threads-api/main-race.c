#include <stdio.h>

#include "common_threads.h"

int balance = 0;

void* worker(void* arg) {
    pthread_mutex_t lock;
    pthread_mutex_lock(&lock);
    balance++; // unprotected access 
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);
    //balance++; // unprotected access
    Pthread_join(p, NULL);
    return 0;
}
