#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <utmp.h>
#include <sys/utsname.h>

int main() {

    int pid;
    int fd[2];
    if(pipe(fd) < 0) exit(1);
    int id = fork();
    if(id == 0) {
        // child process
        printf("\nPrinting pid and ppid from child process\nprocess id = %d, parent process id = %d\n", getpid(), getppid());
        id = fork();
        if(id == 0) {
            // grandchild process
            printf("\nPrinting roll number from grandchild process CSB19047\n");
            pid = getpid();
            write(fd[1], &pid, sizeof(pid));
            printUsers();
        } else if(id > 0) {
            // parent of grandchild process
            wait(NULL);
            pid = getpid();
            write(fd[1], &pid, sizeof(pid));
        } else {
            exit(1);
        }
    } else if(id > 0) {
        // parent process
        wait(NULL);

        pid = getpid();
        write(fd[1], &pid, sizeof(pid));

        while(1) {
            read(fd[0], &pid, sizeof(pid));
            printf("\npid = %d", pid);
        }
        exit(0);
    } else {
        exit(1);
    }

}