#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// observation: when sleep_time is small we can see the resolution of gettimeofday is not great
// but when setting sleep_time to larger values (e.g. 100, 500, 1000 or more) we see the gaps between values much greater than expected
// this is because the scheduler performs context switch and moves to other processes
// futher note: gettimeofday() should not be used to get time intervals, use clock_gettime(3) instead
int main(int argc, char *argv[])
{
    int sleep_time = atoi(argv[1]);
    struct timeval *val1 = malloc(sizeof(struct timeval));
    struct timeval *val2 = malloc(sizeof(struct timeval));
    struct timeval *val3 = malloc(sizeof(struct timeval));
    gettimeofday(val1, NULL);
    usleep(sleep_time);
    gettimeofday(val2, NULL);
    usleep(sleep_time);
    gettimeofday(val3, NULL);
    printf("val 1: %ld: \n", val1->tv_usec);
    printf("val 2: %ld: \n", val2->tv_usec);
    printf("val 3: %ld: \n", val3->tv_usec);
}