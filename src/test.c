#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "parser.h"
#include <crtdbg.h>

int main1(int argc, char argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
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
	removeFromList(&n);
	removeFromList(&n);

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
	Data* d6 = malloc(sizeof(Data));
	char* u1 = "Ray";
	d6->type = "string";
	d6->data = u1;
	Data* d7 = malloc(sizeof(Data));
	char* u2 = "Orange";
	d7->type = "string";
	d7->data = u2;

	addToList(&n2, *d3);
	addToList(&n2, *d4);
	// this should have the same effect as addToList but does not 
	//addToList(&n2, *d5);
	addToListIndex(&n2, 1, *d5);
	addToListIndex(&n2, 1, *d6);
	addToListIndex(&n2, 2, *d7);
	//printf("%d\n", size(n2) - 1);

	printListString(n2);

	// get the data element at index 1 of n2
	//Data* d6 = get(n2, 1);
	//printf("%s\n", (char*) d6->data);

	free(d3);
	free(d4);
	free(d5);
	free(d6);
	free(d7);
	removeFromListIndex(&n2, 2);
	removeFromListIndex(&n2, 1);
	removeFromListIndex(&n2, 1);
	removeFromListIndex(&n2, 0);
	removeFromListIndex(&n2, 0);
	//char* sl = malloc(sizeof(char) * 12);
	return 0;
}

int main(int argc, char argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//char* str = parseFile("test.txt");
	//printf("%s\n", str);
	printf("%d\n", 4);
	//free(str);
	return 0;
}