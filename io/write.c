// write.c

// write to standard output

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define BUFSIZE 4096

int main() {
	char s[] = "Hello!\n";
	ssize_t byteswritten = write(STDOUT_FILENO, s, strlen(s));

	return 0;
}


