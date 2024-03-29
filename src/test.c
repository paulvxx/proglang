#define _CRTDBG_MAP_ALLOC
#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "pparser.h"
#include "programmanager.h"
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

	//char * str = malloc(sizeof(char) * 1024);
	char* str = strdup("variable%%%%");
	int p = 0;
	int c = 0;
	parseVariable(str, &c, &p);
	char *st = substr(str, 0, p);
	printf("%s\n", st);
	free(str);

	str = strdup("12345%%%%");
	p = 0;
	c = 0;
	int res = 0;
	float resf = 0.0;
	parseNumber(str, &c, &p, &res, &resf);
	printf("%d\n", res);

	free(st);
	free(str);

	char* pstr = parseFile("test.txt");
	printf("%s\n", pstr);
	int pos = 0;
	int line = 1;
	int col = 0;
	int error = TRUE;
	Node* program = NULL;
	if(parseProgram(pstr, &line, &col, &pos, &error, &program)) printf("True\n");
	else printf("False\n");

	PrintProgram(program);
	

	char* fparams[] = { "abc", "@ffd" };
	char* fname = "my_function";

	char* fparams2[] = { "b", "red", "g", "h", "code"};
	char* fname2 = "sample_f";

	char* fparams3[] = { "d", "ch", "o", "l", "ms", "uv", "ct" };
	char* fname3 = "example";



	Node* f = createNewFunction(fname, 2, fparams);
	Node* f2 = createNewFunction(fname2, 5, fparams2);
	Node* f3 = createNewFunction(fname3, 7, fparams3);
	//PrintFunction(f);
	//PrintFunction(f2);

	Node* pg = NULL;

	// Add functions to the program
	addFunctionToProg(&pg, f);
	addFunctionToProg(&pg, f2);
	addFunctionToProg(&pg, f3);

	// Print the program
	//PrintProgram(pg);

	// Free the program
	DeleteProgram(pg);
	DeleteProgram(program);

	free(pstr);
	return 0;
}
