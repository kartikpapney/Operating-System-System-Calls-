/*

Write a two C programs named program1.c and program2.c to demonstrate the concept of shared
memory where program1(process1) will be responsible for writing it’s process id and program2(
process2) will be responsible for reading the contents whatever program1(process1) writes.
Moreover try to remove the shared memory segment that is created for your above mentioned
operations properly by using proper system call. Try to demonstrate properly.

*/


/*
    Solution
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main(int argc, char* argv[]) {
    // program to write in shared memory

    int shmid, mode;
    key_t key;
    char *data;

    key = ftok("file.txt", 'R');
    if(key == -1) {
        perror("ftok");
        exit(1);
    }
    
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if(shmid == -1) {
        perror("shmid");
        exit(1);
    }

    data = shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    sprintf(data, "%d", getpid());
    printf("Pid = %s\nSuccessfully Written\n", data);
    exit(0);

    // detaching the pointer from shared memory
    if(shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    } 

    exit(0);

}