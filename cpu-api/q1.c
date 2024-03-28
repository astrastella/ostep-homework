#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int x = atoi(argv[1]);
    printf("hello (pid:%d)\n", (int) getpid());
    ++x;
    int rc = fork();

    if (rc == 0) {
        ++x;
        printf("child (pid:%d), x:%d \n", (int) getpid(), x);
    }
    else {
        ++x;
        printf("parent of %d (pid:%d), x: %d \n", rc, (int) getpid(), x);
    }
    return 0;
}
