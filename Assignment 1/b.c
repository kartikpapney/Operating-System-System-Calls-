#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <utmp.h>
#include <sys/utsname.h>

void printUsers()
{
    struct utmp *n;
    setutent();
    n = getutent();
    printf("LoggedIn Users are : ");
    while (n)
    {
        if (n->ut_type == USER_PROCESS)
        {
            printf("%s ", n->ut_user);
        }
        n = getutent();
    }
    printf("\n");
}

int main() {
    printf("Parent process Executing...\n");
    int pid;
    int fd[2];
    if(pipe(fd) < 0) exit(1);
    int id = fork();
    if(id == 0) {
        // child process
        printf("Child process Execting...\n");
        id = fork();
        if(id == 0) {
            // grandchild process
            printf("Grandchild process execting...\n");
            printUsers();
            printf("Grandchild process finished\n");
        } else if(id > 0) {
            // parent of grandchild process
            wait(NULL);
            printf("Child process finished\n");
        } else {
            exit(1);
        }
    } else if(id > 0) {
        // parent process
        wait(NULL);
        printf("Parent process Finished\n");
    } else {
        exit(1);
    }
}
