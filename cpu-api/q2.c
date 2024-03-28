#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    printf("hello (pid:%d) \n", (int) getpid());
    // if success, fileno = 3 because the first 3 file descriptors are for stdin, stdout, stderr
    int fileno = open("./q2.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    int rc = fork();
    char buffer1[] = "child is here";
    char buffer2[] = "parent is here";

    if (rc == 0) {
        write(fileno, buffer1, sizeof(buffer1));
        printf("child (pid:%d), descriptor:%d \n", (int) getpid(), fileno);
    }
    else {
        write(fileno, buffer2, sizeof(buffer2));
        printf("parent of %d (pid:%d), descriptor: %d \n", rc, (int) getpid(), fileno);
    }
    close(fileno);
    return 0;
}