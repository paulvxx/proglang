#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

int main(int argc, char argv[]) {
	Node* n = NULL;
	Data* d = malloc(sizeof(Data));
	int x = 5;
	d->type = "int";
	d->data = &x;
	Data* d2 = malloc(sizeof(Data));
	int y = 12;
	d2->type = "int";
	d2->data = &y;

	addToList(&n, *d);
	addToList(&n, *d2);

	printListInt(n);
	free(d);
	free(d2);
	free(n);
	return 0;
}
