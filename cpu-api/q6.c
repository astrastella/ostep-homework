#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int rc = fork();
    if (rc==0) {
        printf("child process running\n");
    }
    else {
        int rc_wait = waitpid(rc, NULL, 0);
        printf("rc_wait is %d, rc is %d \n", rc_wait, rc);
    }
    return 0;
}