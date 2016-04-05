// simplefork.c

// A fork, but simple

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	pid_t mypid = fork();
	
	if (mypid == 0)
		printf("Child process %ld\n", (long) getpid());
	else
		printf("Parent process %ld with child process %ld\n", (long) getpid(), (long) mypid);
	
	sleep(3);

	return 0;
}


