//	makeargv.c

//	Tokenize command line

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int errno;

int makeargv(char* s, const char* delimiter, char*** pnargv);

int main(int argc, char** argv) {
	
	char** nargv;
	int num_tokens = makeargv(argv[1], " ", &nargv);

	if (num_tokens == -1)
		return -1;

	// output argument array of strings
        for (int i = 0; i < num_tokens; ++i)
                printf("|%s|\n", nargv[i]);
	
	return 0;
}

int makeargv(char* prev, const char* delimiter, char*** pnargv) {

	// check for valid parameters
	if ((!prev) || (!delimiter) || (!*pnargv)) {
		errno = EINVAL;

		return -1;
	}

	// copy prev so we can destroy the copy
	char* s = malloc(strlen(prev) + 1);

	if (!s)
		return -1;

	strcpy(s, prev);
	
	// finds the number of tokens in the string
	int num_tokens = 0;
	if (strtok(s, " "))
		for(num_tokens = 1; strtok(NULL, " "); ++num_tokens);

	// create an argument array of strings
	*pnargv = malloc((num_tokens + 1) * sizeof(char*));

	if (!*pnargv) {
		int error = errno;
		free(s);
		errno = error;
		return -1;
	}

	(*pnargv)[num_tokens] = NULL;
	
	// copy prev again so it can be destroyed again
	strcpy(s, prev);

	// create argument array of strings
	int pos = 0;
	if ((*pnargv)[pos] = strtok(s, " "))
		for (pos = 1; (*pnargv)[pos] = strtok(NULL, " "); ++pos);

	return num_tokens;
}


