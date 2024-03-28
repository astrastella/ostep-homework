#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int *data = malloc(100*sizeof(int));
    data[100] = 0;
    printf("result of the pointer access: %d \n", data[100]);
    return 0;
}