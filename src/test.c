#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include <crtdbg.h>

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

	// ------------------------------
	Node* n2 = NULL;
	Data* d3 = malloc(sizeof(Data));
	char* s = "Hello";
	d3->type = "string";
	d3->data = s;
	Data* d4 = malloc(sizeof(Data));
	char* t = "David";
	d4->type = "string";
	d4->data = t;
	Data* d5 = malloc(sizeof(Data));
	char* u = "Asburn";
	d5->type = "string";
	d5->data = u;
	printf("\n");

	addToList(&n2, *d3);
	addToList(&n2, *d4);
	// this should have the same effect as addToList but does not 
	//addToList(&n2, *d5);
	addToListIndex(&n2, 1, *d5);
	//printf("%d\n", size(n2) - 1);

	printListString(n2);
	free(d3);
	free(d4);
	free(d5);
	free(n2);

	return 0;
}
