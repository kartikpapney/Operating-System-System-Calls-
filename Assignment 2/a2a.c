#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void function() {
	int id = fork();
    printf("Process ID(pid)=%d, Parent Process ID(ppid)=%d\n", getpid(), getppid());
}

int main() {
    // signal(SIGINT, function);
    printf("%d\n", getpid());
    while(1);
}