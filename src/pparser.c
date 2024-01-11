#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pparser.h"

char* parseFile(char* filename) {
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	size_t capacity = 1;
	char *result = (char*) malloc(sizeof(char) * capacity);
	result[0] = '\0';
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Error opening file\n");
		exit(EXIT_FAILURE);
	}

	// read file line by line
	// increase capacity of result if necessary

	while ((strlen(result)+1) >= capacity) {
		capacity *= 2;
		result = (char*) realloc(result, sizeof(char) * capacity);
		while (fgets(line, capacity, fp) != NULL) {
			strcat(result, line);
		}
	}

	fclose(fp);
	if (line) free(line);
	return result;
}