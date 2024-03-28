#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int rc = fork();

    if (rc == 0) {
        printf("hello\n");
    }
    else {
        //wait(NULL);
        // by calling usleep the scheduler would want to utilize the cpu resource by switching to the child process if it is not already run
        usleep(1000);
        printf("goodbye\n");
    }
    return 0;
}