/*
  tcopyfile.c

  Copies an input source file to multiple output files.
  Output files are in the form <outputfilename>.<number>
  where the outputfilename is given on the command line, and the
  number is from 0 to the length - 1 given on the command line

  Demonstration of pthreads and io

  Michael L. Collard
  collard@uakron.edu
*/

#include "copyfile.h"

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define R_FLAGS O_RDONLY
#define W_FLAGS (O_WRONLY | O_CREAT)
#define W_PERMS (S_IRUSR  | S_IWUSR) 

#define MAXFILENAME 512

struct copy_t {
  int infd;
  int outfd;
  int status;
  pthread_t tid;
};

void* copyfile_thread(void* args) {

  struct copy_t* copyinfo = args;

  int totalbytes = 0;
  copyfile(copyinfo->infd, copyinfo->outfd, &totalbytes);
}

int main(int argc, char* argv[]) {

  // see how many copies to make
  int numcopiers = atoi(argv[3]);

  // copy the files
  struct copy_t* copyinfo = calloc(numcopiers, sizeof(struct copy_t));
  for (int i = 0; i < numcopiers; ++i) {

    // open the input filename
    int infd = open(argv[1], R_FLAGS);

    // form the output filename
    char filename[MAXFILENAME];
    snprintf(filename, MAXFILENAME, "%s.%d", argv[2], i + 1);

    fprintf(stderr, "%s\n", filename);

    // open the output file
    int outfd = open(filename, W_FLAGS, W_PERMS);

    // use the thread to copy the file
    copyinfo[i].infd = infd;
    copyinfo[i].outfd = outfd;
    pthread_create(&copyinfo[i].tid, copyfile_thread, NULL, &copyinfo[i]);
  }

#if 0
  int infd = STDIN_FILENO;
  if (argc > 1) {
    infd = open(argv[1], O_RDONLY);
  }
  if (infd < 0) {
    perror("Input open error");
    return 1;
  }
  
  int outfd = STDOUT_FILENO;
  if (argc > 2) {
    outfd = open(argv[2], O_WRONLY, O_CREAT);
  }
  if (outfd < 0) {
    perror("Output open error");
    return 1;
  }

  // copy the file
  int totalbytes = 0;
  copyfile(infd, outfd, &totalbytes);
  
  // close the input file
  if (infd != STDIN_FILENO)
    close(infd);
  
  // close the output file
  if (outfd != STDOUT_FILENO)
    close(outfd);
#endif
  
  return 0;
}
