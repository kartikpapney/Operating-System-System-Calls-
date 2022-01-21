/*
Problem:

Write a C program to get the process submission time & finished time of a process. For this
assignment your C program will create a child process and writes the submission and finished time of
the child process into a file. Learn about times() system call.
Also learn about use of gettimeofday() system call.

*/


/*
Solution
*/
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utmp.h>

int main()
{

    pid_t child;
    child = fork();
    if (child < 0) {
        perror("Fork error.");
        exit(1);
    } else if (child == 0) {
        int i, j;
        for (i = 0; i < 100000; i++)
            for (j = 0; j < 10000; j++);
        exit(0);
    }
    else {
        struct timeval before, after;
        gettimeofday(&before, NULL);
        wait(NULL);
        gettimeofday(&after, NULL);

        FILE *fp;
        fp = fopen("time_stamp.txt", "w");
        fprintf(fp, "Submission time: %ld seconds\n", before.tv_sec);
        fprintf(fp, "Termination time: %ld seconds\n", after.tv_sec);
        fprintf(fp, "Execution time: %ld seconds", after.tv_sec - before.tv_sec);
        exit(0);
    }
    exit(0);
}