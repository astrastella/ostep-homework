#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int rc = fork();
    if (rc==0) {
        close(STDOUT_FILENO);
        open("./q4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

        char *myargs[2];
        myargs[0] = strdup("/bin/ls");
        myargs[1] = NULL;
        execv(myargs[0], myargs);
    }
    else{
        wait(NULL);
    }
    return 0;
}