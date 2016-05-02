/*
  trimoutput.c

  Cuts the end off output.

  Michael L. Collard
  collard@uakron.edu
*/

#define _GNU_SOURCE
#include <unistd.h>
#include <dlfcn.h>
#include <stdio.h>

ssize_t write(int fd, const void *buf, size_t count) {

  puts("MY WRITE");
  
  static ssize_t (*_real_write)(int fd, const void *buf, size_t count) = NULL;

  if (_real_write == NULL) {

    _real_write = dlsym(RTLD_NEXT, "write");
   if (_real_write == NULL)
     return 0;
  }

  return _real_write(fd, buf, count >= 10 ? count - 10 : count) + (count >= 10 ? 10 : 0);
}








