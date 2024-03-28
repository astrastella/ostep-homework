#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

// takes one argument: amount of memory in MB it will use
int main(int argc, char *argv[])
{
    printf("memory-user running: process id %d \n", getpid()); //for use with pmap to inspect memory for this process
    int mem = atoi(argv[1]);
    int mb_to_bytes = (int) pow(2, 20);
    size_t n = mem * mb_to_bytes / sizeof(int);
    printf("preparing to allocate %zu bytes of memory \n", n*sizeof(int)); 
    //in pamp we note the memory in heap for this is actually (n+1)*sizeof(int) due to bookeeping info and alignment
    int *arr = calloc(n, sizeof(int));
    int i = 0;

    while(1) {
        for (i; i < n; ++i) {
            arr[i] = i;
        }
    }

    free(arr);
    return 0;
}