// Submitted By CSB19047 - Kartik Papney

/*

Write a C program to handle the reception of INTERRUPT FROM THE
KEYBOARD signal by executing a particular (user) function, which function is
responsible for creating a child process by using fork() system call. Also, the child
process will take an input N (N is the no. of terms to generate the Fibonacci series)
from the user and generate the Fibonacci series up to N terms. Then the child
process will send the Fibonacci series terms one by one to the parent process by
using pipe() system call and the parent process will read the Fibonacci series terms
one by one and will display it.
(N.B. – Before sending the Fibonacci terms one by one from the child
process, first you send the Process ID of the child process to the parent process and
read and display it in the parent process. Again after sending the terms one by one
from the child process to the parent process, from the child process you send the
Signal ID for which handler function has been generated and read and display it in
the parent process.)

*/

// CPP program to illustrate
// default Signal Handler
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

void user_function(int sigid) {
    int fd[2];
    if(pipe(fd) == -1) {
        printf("Can't perform pipe system call\n");
        exit(1);
    } 
    pid_t id = fork();
    if(id == 0) {
        // child process
        pid_t pid = getpid();
        int n, a = 0, b = 1, c;
        write(fd[1], &pid, sizeof(pid));
        
        printf("\nNow Enter number of fibanacci terms: ");
        scanf("%d", &n);
        write(fd[1], &n, sizeof(n));
        while(n-- != 0) {
            write(fd[1], &a, sizeof(a));
            c = a + b;
            a = b;
            b = c;
        }
        write(fd[1], &sigid, sizeof(sigid));
        exit(0);
    } else if(id > 0) {
        // parent process
        int child_pid, n, c, signal_id, status;
        wait(&status);
        read(fd[0], &child_pid, sizeof(child_pid));

        printf("\nChild pid recieved from child process: %d\n", child_pid);
        read(fd[0], &n, sizeof(n));

        printf("\nNumber of fibonacci terms = %d\n", n);
        while(n-- != 0) {
            read(fd[0], &c, sizeof(c));
            printf("%d, ", c);
        }

        printf("\n");
        read(fd[0], &signal_id, sizeof(signal_id));
        printf("\nSignal Id recieved from child process: %d\n", signal_id);
    } else {
        printf("Error in fork system call!!\n");
        exit(1);
    }
}

int main()
{
    printf("Press Ctrl + c for running the handler function OR Ctrl + Z to end the program\n");
    signal(SIGINT, user_function);
    // user_function();
    while (1) {
        // fflush(stdin);
    };
    return 0;
}