/*
  copyfile.c

  Read from standard input and echo to standard output
*/

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 4096

int copyfile(int infd, int outfd, int* totalbytes) {

  char buf[BUFSIZE];

  while (1) {

    // read a block
    ssize_t bytesread = read(infd, buf, BUFSIZE);
    if ((bytesread == -1) && (errno == EINTR))
      continue;
    if (bytesread == -1) {
      puts("I HAD AN ERROR");
      return 1;
    }
    if (bytesread == 0)
      break;

    // write the block that was read
    ssize_t byteswrote;
    while (((byteswrote = write(outfd, buf, bytesread)) == -1) &&
	   (errno == EINTR))
      ;

    // "real" write error
    if (byteswrote == -1)
      return 1;
  }

  return 0;
}
