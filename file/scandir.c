/*
  scandir.c

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
#include <stdlib.h>

int dir_filter(const struct dirent* d) {

  return d->d_name[0] != '.';
}

int listdir(const char* dirname) {

  // collect all the filenames in the directory
  struct dirent** namelist;
  int n = scandir(dirname, &namelist, dir_filter, alphasort);

  // output the names in the directory
  for (int i = 0; i < n; ++i) {

    struct dirent* direntp = namelist[i];
    
    char path[256];
    sprintf(path, "%s/%s", dirname, direntp->d_name);
    printf("%s\n", path);

    if (direntp->d_type == DT_DIR)
      listdir(path);

  }
  
  // free the namelist
  for (int i = 0; i < n; ++i)
    free(namelist[i]);
  free(namelist);
  
  /*
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
    
  }
  
  // close the directory
  closedir(dirp);
  */
  
  return 0;
}

int main(int argc, char* argv[]) {

  listdir(argv[1]);
  
  return 0;
}
