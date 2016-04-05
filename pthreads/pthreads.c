// pthreads.c

// A plethora of threads

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>

struct threaddata_t {
	int id;
	int status;
	pthread_t tid;
};

//do something in a pthread
void* process_thread(void* args) {
	// unpack args
	struct threaddata_t* data = args;

	// trace that we started
	fprintf(stderr, "Process %d starting\n", data->id);

	//trace that we ended
	fprintf(stderr, "Process %d ending\n", data->id);

	return &(data->status);
}

int main(int argc, char* argv[]) {
	// make sure we have the number of threads
	if (argc < 2) {
		fprintf(stderr, "Usage: %s threads\n", argv[0]);
		return 1;
	}

	// number of threads
	int numthreads = atoi(argv[1]);

	// create the threads
	struct threaddata_t* threadinfo = calloc(numthreads, sizeof(struct threaddata_t));

	// wait for the threads to finish
	for ( int i = 0; i < numthreads; ++i) {
		//threadinfo[i].id = i;

		fprintf(stderr, "Main %d waiting\n", threadinfo[i].id);

		// use thread to do some work
		//pthread_create(&threadinfo[i].tid, NULL, process_thread, &threadinfo[i]);

		pthread_join(threadinfo[i].tid, NULL);

		fprintf(stderr, "Main %d finished\n", threadinfo[i].id);
	}

	return 0;
}


