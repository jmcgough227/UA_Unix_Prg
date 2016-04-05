// fileinfo.c

// Information about a file

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

int main(int argc, char* argv[]) {
	// get the file info
	struct stat statbuf;
	int status = stat(argv[1], &statbuf);
	if (status == -1) return 1;

	// output some stuff
	printf("File size: %d\n", (int)statbuf.st_size);
	printf("Block size: %d\n", (int)statbuf.st_blksize);

	// output file type
	printf("File type: ");
	if (S_ISDIR(statbuf.st_mode))
		puts("directory\n");
	else if (S_ISREG(statbuf.st_mode))
		puts("regular\n");
	else
		puts("u wot m8?\n");

	// output time of last access
	printf("Last access: %s", ctime(&statbuf.st_atime));

	return 0;
}
