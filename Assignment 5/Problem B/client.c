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

struct message_queue
{
    long type;
    char message[200];
} a;

int main()
{
    int queue_id;
    key_t key = ftok("/tmp/FIFO", 'A');

    queue_id = msgget(key, 0666 | IPC_CREAT);
    msgrcv(queue_id, &a, sizeof(a), 1, 0);
    printf("\nMessage received: %s\n", a.message);
    msgctl(queue_id, IPC_RMID, NULL);
    return 0;

}