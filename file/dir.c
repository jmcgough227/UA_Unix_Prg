/*
  dir.c

  List files in a directory

  Michael L. Collard
  collard@uakron.edu
*/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <dirent.h>
#include <string.h>

int listdir(const char* dirname) {

  // open the directory
  DIR* dirp = opendir(dirname);
  if (!dirp) {
    perror(dirname);
    return -1;
  }

  // output the full path of all names in the directory
  struct dirent* direntp = 0;
  while ((direntp = readdir(dirp)) != NULL) {
    if (strcmp(".", direntp->d_name) == 0)
      continue;
    if (strcmp("..", direntp->d_name) == 0)
      continue;
    
    char path[256];
    sprintf(path, "%s/%s", dirname, direntp->d_name);
    printf("%s\n", path);

    if (direntp->d_type == DT_DIR)
      listdir(path);
  }
  
  // close the directory
  closedir(dirp);
  
  return 0;
}

int main(int argc, char* argv[]) {

  listdir(argv[1]);
  
  return 0;
}
