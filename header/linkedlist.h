#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Data {
	char* type;
	void* data;
} Data;

typedef struct Node {
	Data data;
	struct Node* next;
} Node;

void addToList(Node** list, Data data);

void printListInt(Node* list);

void printListString(Node* list);
