/*
  decompress.c

  Decompress a file encoded with anything (?)
  
  Michael L. Collard
  collard@uakron.edu
*/

#include <archive.h>
#include <archive_entry.h>

int main(int argc, char* argv[]) {

  // setup the archive object
  struct archive* a = archive_read_new();
  archive_read_support_filter_all(a);
  archive_read_support_format_raw(a);

  // actually open the archive file
  int r = archive_read_open_filename(a, argv[1], 10240);
  if (r != ARCHIVE_OK)
    return 1;

  // go to the first header
  struct archive_entry *entry;
  r = archive_read_next_header(a, &entry);
  if (r != ARCHIVE_OK)
    return 1;

  // output the data
  char buf[512];
  int bufsize = 512;
  for (;;) {
    int size = archive_read_data(a, buf, bufsize);
    if (size < 0)
      return 1;

    if (size == 0)
      break;

    write(1, buf, size);
  }

  // close it up
  r = archive_read_close(a); 
  if (r != ARCHIVE_OK)
    return 1;

  return 0;
}
