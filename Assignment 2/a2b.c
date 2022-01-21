/*
	CSB19047
    Kartik Papney

    
	Assignment 2(b):

	Write a C program which will take the Process ID and signal ID as input to
	demonstrate the use of kill( ) system call.
	You need to put explanatory comment in your program to demonstrate the
	purpose and why you have used the system calls
	Hints:
	* For demonstrating so, you modify the assignment 2(a) to handle each and every signal
	(as possible as). Run command kill -l, to know about signal type and ID. Now run the
	modified assignment 2(a).
	* Again from another terminal, run the assignment 2(b) which will take the Process ID
	of the modified assignment 2(a) and any valid signal value as input.
	* Your signal handler function of the modified assignment 2(b) should be able to
	display the signal ID of the generated signal.
	* To know more about kill( ), see kill(2) man page and for signal type, value, action
	and comment, see signal(7) man page.

*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>


int main(int argc, char *argv[]) {

	// Run Command: ./a.out {PROCESS_ID}

	int pid = 18793;
	// if(argc != 2) {
	// 	printf("Invalid\n");
	// 	exit(1);
	// }
	// pid = atoi(argv[1]);
	// This will kill the process with pid={pid} on SIGINT interrupt call(CTRL + C);
	kill(pid, SIGINT);
    exit(0);
}