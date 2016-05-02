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
#include <stdlib.h>

void* malloc(size_t size) {

  puts("MY malloc");
  
  static void* (*_real_malloc)(size_t count) = NULL;

  if (_real_malloc == NULL) {

    _real_malloc = dlsym(RTLD_NEXT, "malloc");
    if (_real_malloc == NULL) {
      puts("PROBLEM");
      return 0;
    }
  }

  return _real_malloc(size);
}








