#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int rc = fork();
    if (rc==0) {
        int rc_wait = wait(NULL);
        printf("wait returned %d", rc_wait);
    }
    return 0;
}