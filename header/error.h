#include <stdio.h>
#include <stdlib.h>

void generateError(char* file, size_t line, size_t pos, char* message) {
	fprintf(stderr, "File: %s, Line=%zd, pos=%zd: %s\n", file, line, pos, message);
	exit(1);
}

