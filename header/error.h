#include <stdio.h>
#include <stdlib.h>

void generateError(file, line, pos, message) {
	fprintf(stderr, "File: %s, Line=%d, pos=%d: %s\n", file, line, pos, message);
	exit(1);
}

