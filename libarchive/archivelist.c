/*
  archivelist.c

  List the names of the files is an archive.
  
  Michael L. Collard
  collard@uakron.edu
*/

#include <archive.h>
#include <archive_entry.h>

int main(int argc, char* argv[]) {

  // setup the archive object
  struct archive* a = archive_read_new();
  archive_read_support_filter_all(a);
  archive_read_support_format_all(a);

  // actually open the archive file
  int r = archive_read_open_filename(a, argv[1], 10240); // Note 1
  if (r != ARCHIVE_OK)
    return 1;

  // read through the entries
  struct archive_entry *entry;
  while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {

    // output the path to the archived file
    puts(archive_entry_pathname(entry));

    // move over the data part of the archive entry
    archive_read_data_skip(a);
  }

  // close it up
  r = archive_read_close(a); 
  if (r != ARCHIVE_OK)
    return 1;

  return 0;
}
