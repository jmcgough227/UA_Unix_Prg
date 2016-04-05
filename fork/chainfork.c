// chainfork.c

// A plethora chain of forks

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>

int main(int argc, char* argv[]) {
	// make sure we have the number of children
	if (argc < 2) {
		fprintf(stderr, "Usage: %s processes\n", argv[0]);
		return 1;
	}

	// number of children
	int n = atoi(argv[1]);

	// chain out n children
	pid_t childid = 0;
	int i;
	for (i = 0; i < n; ++i)
		if ((childid = fork()) != 0)
			break;

	// simulate a random amount of processing
	srand(time(NULL) * i);
	sleep(rand() % 4);

	// parent wait for the children
	if (childid > 0) {
		while ((childid = wait(NULL))) {
			if (errno == ECHILD)
				break;
		}
	}

	fprintf(stderr, "i: %d Processing: process ID: %ld parent ID: %ld child ID: %ld\n", 
		i, (long) getpid(), (long) getppid(), (long) childid);

	return 0;
}


