/*
  src2srcmlopts.c

  src2srcml conversion program command-line option handling.

  Michael L. Collard
  collard@uakron.edu
*/

#include <stdio.h>
#include <getopt.h>

extern char* optarg;
extern int optind, opterr, optopt;

struct option_ext {
  const char* name;
  int has_arg;
  int* flag;
  int val;
  int val2;
};

struct option_ext longopts[] = {
  { "help",               no_argument,       NULL, 'h', 2 },
  { "version",            no_argument,       NULL, 'V', 4 },

  { "encoding",           required_argument, NULL, 'E', 8 },
  { "src-encoding",       required_argument, NULL, 'S', 16 },

  { "no-xml-declaration", no_argument,       NULL, 'N', 32 },

  { "verbose",            no_argument,       NULL, 'v', 64 },

  { "language",           required_argument, NULL, 'l', 128 },
};

int main(int argc, char** argv) {

  int flag = 0;
  int option_result;
  int oc;
  int longindex;
  while ((oc = getopt_long(argc, argv, "hVESXNvl:", (struct option*) longopts, &longindex)) != -1) {

    // invalid options
    if (oc == '?') {
      fprintf(stderr, "-%c\n", oc);
      continue;
    }

    fprintf(stderr, "%d\n%c\n", longindex, oc);
    //continue;

    // mark the right flag
    flag |= longopts[longindex].val2;

    // generic argument reporter
    fprintf(stderr, "--%s", longopts[longindex].name);
    if (longopts[longindex].has_arg == required_argument)
      fprintf(stderr, "=%s", optarg);
    fprintf(stderr, "\n");
    continue;

    switch (oc) {
    case 'h':
      fprintf(stderr, "--help\n");
      break;
    case 'V':
      fprintf(stderr, "--version\n");
      break;
    case 'E':
      fprintf(stderr, "--encoding=%s\n", optarg);
      break;
    case 'S':
      fprintf(stderr, "--src-encoding=%s\n", optarg);
      break;
    case 'N':
      fprintf(stderr, "--no-xml-declaration=%s\n", optarg);
      break;
    case 'v':
      fprintf(stderr, "--verbose\n");
      break;
    case 'l':
      fprintf(stderr, "--language=%s\n", optarg);
      break;

    default:

      break;
    };
  }

  fprintf(stderr, "flag=%d\n", flag);

  return 0;
}
