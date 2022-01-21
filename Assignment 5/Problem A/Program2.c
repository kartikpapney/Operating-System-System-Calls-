/*
    Write a C program called Program1 which is responsible for creating a named PIPE or FIFO with
    necessary permission for all users by using the mknod( ) system call. Now, you keep the facility to
    read the information from the FIFO if any other process write some information into the FIFO and as
    well as keep the facility to write some information into the FIFO, so that Program2 can read it.
    Again write another C program called Program2 which is responsible for taking the user input and
    write it back to the FIFO so that Program1 can read it. Moreover, you have to provide the facility to
    read the FIFO in this program.
    (N.B. - First run the Program1 and keep it in running state in the background. Then run the Program2
    which will take user input string and write the input string into the FIFO. Then Program1 will read it
    from the FIFO and display it and after that Program1 will write something into the FIFO as
    ACKNOWLEDGEMENT and program2 will read the ACKNOWLEDGEMENT string from the
    FIFO. In Program2, you may take the input string as a command line argument)

*/



#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int memory_size = 100;
int main() {
    int fd;
    char* FIFO = "/tmp/FIFO";
    char shared_memory[memory_size];
    mknod(FIFO, S_IFIFO | 0666, 0);
    
    printf("Instructions\n1. First enter message in program1\n2. You'll recieve messsage in program2\n3. Enter message in program2\n4. You'll recieve message in program1\nrepeat...\n");
    fflush(stdin);
    
    while(1) {
	int i;
        fd = open(FIFO, O_RDONLY);
        printf("You'll recieve a message from program1\n");
        read(fd, shared_memory, sizeof(shared_memory));
        printf("You recieved a message: %s", shared_memory);

        for(i=0; i<memory_size; i++) shared_memory[i] = 0;

        fd = open(FIFO, O_WRONLY);
        printf("Please enter your message: ");
        fgets(shared_memory, memory_size, stdin);
        write(fd, shared_memory, memory_size);
        
    }
    return 0;
}
