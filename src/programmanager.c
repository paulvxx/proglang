#include <stdio.h>
#include <stdlib.h>
#include "programmanager.h"

Node* createNewFunction(char* fName, int paramc, char* fparamss[]) {

	// creates a new function node with the given name and parameters, stored in an array of strings
	char** flist = (char**) malloc(sizeof(char*) * (paramc+2));

	// first element of the array is the function name
	flist[0] = strdup(fName);

	// the rest of the elements are the parameters
	for (int i = 1; i <= paramc; i++) {
		flist[i] = strdup(fparamss[i-1]); //malloc(sizeof(char) * (strlen(fparams[i])+1));
	}

	// used to mark the end of the array
	flist[paramc + 1] = NULL;

	Node* newNode = (Node*)malloc(sizeof(Node));
	Data data = {"Function", (void*) flist};
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

void DeleteFunction(Node* function) {
	if (function != NULL) {
		char** flist = (char**) function->data.data;
		for(int i = 0; flist[i] != NULL; i++) {
			free(flist[i]);
		}
		free(flist);
		free(function);
		function = NULL;
	}
}

void PrintFunction(Node* function) {
	if (function != NULL) {
		char** flist = (char**) function->data.data;
		printf("[");
		for(int i = 0; flist[i] != NULL; i++) {
			printf("%s ", flist[i]);
		}
		printf("]\n");
	}
}

void PrintProgram(Node* program) {
	if (program != NULL) {
		Node* current = program;
		while (current != NULL) {
			PrintFunction(current->data.data);
			current = current->next;
		}
	}
}

void DeleteProgram(Node* program) {
	if (program != NULL) {
		Node* current = program;
		while (current != NULL) {
			Node* next = current->next;
			DeleteFunction(current->data.data);
			free(current);
			current = next;
		}
		program = NULL;
	}
}

void addFunctionToProg(Node** program, Node* newFunction) {
	Data ref = {"Reference", (void*) newFunction};
	addToList(program, ref);
}
