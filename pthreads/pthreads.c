/*
  pthreads.c

  A plethora of threads

  Michael L. Collard
  collard@uakron.edu
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>

struct threaddata_t {
  int id;
  int status;
  pthread_t tid;
};

// do something in a pthread
void* process_thread(void* args) {

  // unpack the args
  struct threaddata_t* data = args;

  // trace that we started
  fprintf(stderr, "Process %d starting\n", data->id);
  
  // trace that we ended
  fprintf(stderr, "Process %d ending\n", data->id);

  return &(data->status);
}

int main(int argc, char* argv[]) {

  // make sure we have the number of children
  if (argc < 2) {
    fprintf(stderr, "Usage:   %s threads\n", argv[0]);
    return 1;
  }

  // number of threads
  int numthreads = atoi(argv[1]);

  // create the threads
  struct threaddata_t* threadinfo = calloc(numthreads, sizeof(struct threaddata_t));
  for (int i = 0; i < numthreads; ++i) {

    threadinfo[i].id = i;

    // use the thread to do some work
    pthread_create(&threadinfo[i].tid, NULL, process_thread, &threadinfo[i]);

    // trace that we started
    fprintf(stderr, "Main %d starting\n", threadinfo[i].id);

  }

  // wait for all the threads to finish
  for (int i = 0; i < numthreads; ++i) {

    fprintf(stderr, "Main %d waiting\n", threadinfo[i].id);

    pthread_join(threadinfo[i].tid, NULL);

    fprintf(stderr, "Main %d finished\n", threadinfo[i].id);
  }
  
  return 0;
}
