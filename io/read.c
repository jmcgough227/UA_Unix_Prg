// read.c

// read from standard input and print out

#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define BUFSIZE 4096

int main() {
	char buf[BUFSIZE + 1];
	
	while(1) {
		ssize_t bytesread = read(STDIN_FILENO, buf, BUFSIZE);

		if ((bytesread == -1) && (errno == EINTR))
			continue;

		if (bytesread == -1) {
                        puts("I HAD AN ERROR");
                        return 1;
                }

		if (bytesread == 0)
			break;		

		buf[bytesread] = 0;
		printf("Read %zd bytes: %s\n", bytesread, buf);
	}

	return 0;
}


