#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int rc = fork();
    if (rc==0) {
        close(STDOUT_FILENO);
        printf("child here: trying to print\n"); //undefined behavior (in my case, nothing happens)
    }
    return 0;
}