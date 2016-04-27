/*
  env.c

  Check out the environment of a program.

  Michael L. Collard
  collard@uakron.edu
*/

#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[], char* environ[]) {

  int i = 0;
  for ( ; environ[i]; ++i) {
    write(STDOUT_FILENO, environ[i], strlen(environ[i]));
    write(STDOUT_FILENO, "\n", 1);
  }

  return 0;
}
