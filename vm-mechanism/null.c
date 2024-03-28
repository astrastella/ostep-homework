#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int *ptr = malloc(sizeof(int));
    ptr = NULL;
    printf("result of the pointer access: %d \n", *ptr); //segmentation fault
    return 0;
}