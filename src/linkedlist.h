#include <stdio.h>
#include <stdlib.h>

typdef struct {
	char* type;
	void* data;
} Data;

typedef struct Node {
	Data data;
	struct Node* next;
} Node;

void addToList(Node* list, Data data);

void printList(Node* list);