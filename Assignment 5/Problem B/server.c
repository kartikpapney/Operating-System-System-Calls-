/*
Write a two C programs to be one client program and one server program so that you can demonstrate the
IPC mechanism using Message Queue functionality.
* Print the message queue ID in the stderr file.
* Put attention in the command macros used in msgctl( ).
*/



#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
//message queue node structure
struct message_queue
{
    long type;
    char message[200];
} a;

int message_size = 100;

int main()
{
    int queue_id;
    key_t key = ftok("/tmp/FIFO", 'A');
    printf("Enter Your Message: ");

    fgets(a.message, message_size, stdin);
    a.type = 1;

    queue_id = msgget(key, 0666 | IPC_CREAT);
    if (msgsnd(queue_id, &a, sizeof(a), 0) == 0) {
        printf("\nMessage sent: %s\n", a.message);
    }
    return 0;
}