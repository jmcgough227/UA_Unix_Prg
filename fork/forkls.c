// forkls.c

// Fork an ls command

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	pid_t mypid = fork();

	if (mypid == 0) {
		printf("Child process %ld\n", (long) getpid());
		execlp("ls", "ls", "-l", NULL);

		return 1;
	}
	else {
		printf("Parent process %ld with child process %ld\n", (long) getpid(), (long) mypid);

		wait(0);

		printf("Child process %ld is now done\n", (long) mypid);
	}

	return 0;
}


