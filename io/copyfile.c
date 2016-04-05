// copyfile.c

// read from standard input and echo to standard output

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 4096

int main(int argc, char* argv[]) {

	int infd = STDIN_FILENO;
	if (argc > 1) {
		infd = open(argv[1], O_RDONLY);
	}

	if (infd < 0) {
		perror("Input open error");
		return 1;
	}

	int outfd = STDOUT_FILENO;
	if (argc > 2) {
		outfd = open(argv[2], O_WRONLY, O_CREAT);
	}

	if (outfd < 0) {
		perror("Output open error");
		return 1;
	}

	char buf[BUFSIZE + 1];
	
	while(1) {
		// read a block
		ssize_t bytesread = read(infd, buf, BUFSIZE);

		if ((bytesread == -1) && (errno == EINTR))
			continue;

		if (bytesread == -1) {
                        puts("I HAD AN ERROR");
                        return 1;
                }

		if (bytesread == 0)
			break;		

		// write the block that was read
		ssize_t byteswrote;
		while(((byteswrote = write(outfd, buf, bytesread)) == -1) 
			&& (errno == EINTR));

		// "real" write error
		if (byteswrote == -1)
			return 1;
	}

	// close the input file
	if (infd != STDIN_FILENO)
		close(infd);

	// close the output file
	if (outfd != STDOUT_FILENO)
		close(outfd);

	return 0;
}


