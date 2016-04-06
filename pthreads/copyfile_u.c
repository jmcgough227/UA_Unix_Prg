/*
  copyfile_u.c

  Read from standard input and echo to standard output
*/

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "copyfile.h"

int main(int argc, char* argv[]) {

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
  
  return 0;
}
