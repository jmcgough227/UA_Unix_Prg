/*
  copyfile.h

  Read from standard input and echo to standard output
*/

#ifndef INCLUDED_COPYFILE_H
#define INCLUDED_COPYFILE_H

// copies from file infd to file outfd, reporting the total number of bytes
int copyfile(int infd, int outfd, int* totalbytes);

#endif

