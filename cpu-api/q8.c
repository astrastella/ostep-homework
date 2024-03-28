#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int pipefd[2];
    if (pipe(pipefd) ==-1 ) {
        exit(EXIT_FAILURE);
    }
    int rc1 = fork();
    if (rc1==0) {
        close(pipefd[0]); // read end
        dup2(pipefd[1], STDOUT_FILENO); //connects the standard output to the pipe
        close(pipefd[1]); // write end
        printf("hello from first child");
    }
    else {
        int rc2 = fork();
        if (rc2==0) {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO); //connects the standard input to the pipe
            close(pipefd[0]);
            char buf[BUFSIZ];
            read(STDIN_FILENO, buf, BUFSIZ);
            printf("hello from second child\n");
            printf("reading from the pipe: %s \n", buf);
        }
        else {
            waitpid(rc1, NULL, 0);
            waitpid(rc2, NULL, 0);
        }
    }
    
    return 0;
}