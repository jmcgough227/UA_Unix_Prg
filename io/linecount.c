// linecount.c

// Counts the lines in the listed files

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>

#define BUFSIZE 4096

int main(int argc, char* argv[]) {

	// input file 1
	int infd1 = STDIN_FILENO;
	if (argc > 1) {
		infd1 = open(argv[1], O_RDONLY);
	}

	if (infd1 < 0) {
		perror("Input open error");
		return 1;
	}

	// input file 2
	int infd2 = STDIN_FILENO;
	if (argc > 2) {
		infd2 = open(argv[2], O_RDONLY);
	}

	if (infd2 < 0) {
		perror("Input open error");
		return 1;
	}

	//setup for select monitoring
	fd_set readset;
	FD_ZERO(&readset);
	FD_SET(infd1, &readset);
	FD_SET(infd2, &readset);

	int maxfd = infd1 > infd2 ? infd1 : infd2;

	char buf[BUFSIZE + 1];
	int lines = 0;
	int numfiles = 2;
		
	while(1) {
		// block until one of the files is open for reading
		fd_set curreadset = readset;
		int num = 0;

		if (((num = select(maxfd + 1, &curreadset, NULL, NULL, NULL)) != -1)
				&& (errno == EINTR))
			continue;

		if (num == -1)
			break;

		// which input file to read from
		int infd;
		
		if (FD_ISSET(infd1, &curreadset)) {
			infd = infd1;
			puts(argv[1]);
		}
		else if (FD_ISSET(infd2, &curreadset)) {
			infd = infd2;
			puts(argv[2]);
		}
		else {
			break;
		}

		// read a block
		ssize_t bytesread = read(infd, buf, BUFSIZE);

		if ((bytesread == -1) && (errno == EINTR))
			continue;

		if (bytesread == -1) {
                        puts("I HAD AN ERROR");
                        return 1;
                }

		if (bytesread ==0) {
			// done with that input file
			FD_CLR(infd, &readset);
			--numfiles;

			if (numfiles == 0)
				break;	
		}	

		// increment the number of newlines in this block
		for(int i = 0; i < bytesread; ++i)
			if (buf[i] == '\n')
				++lines;
	}

	// close the input file
	if (infd1 != STDIN_FILENO)
		close(infd1);

	// close the output file
	if (infd2 != STDIN_FILENO)
		close(infd2);

	printf("Lines: %d\n", lines);

	return 0;
}


