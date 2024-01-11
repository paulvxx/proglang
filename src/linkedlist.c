#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"


void addToList(Node** list, Data data) {
	// add first element to list
	printf("adding member %s\n", data.type);
	if (*list == NULL) {
		*list = malloc(sizeof(Node));
		(*list)->data = data;
		(*list)->next = NULL;
	} else {
		// add element to end of list
		Node *in = *list;
		while (in->next != NULL) {
			in = in->next;
		}

		Node *n = malloc(sizeof(Node));
		n->data = data;
		n->next = NULL;
		in->next = n;
	}
}

void addToListIndex(Node** list, int index, Data data) {
	if (index == size(*list)) addToList(list, data);
	else if (index == 0) {
		Node* n = malloc(sizeof(Node));
		n->data = data;
		n->next = *list;
		*list = n;
	} else {
		Node* n = *list;
		int i = 0;
		while (i < (index-1)) {
			n = n->next;
			i++;
		}
		Node* newNode = malloc(sizeof(Node));
		newNode->data = data;
		newNode->next = n->next;
		n->next = newNode;
	}
}

void printListInt(Node* list) {
	Node* n = list;
	int index = 0;
	while (n != NULL) {
		// print the value the data points to if the data is of type int
		if (strcmp(n->data.type, "int")==0) {
			printf("%d -> ", *(int*)n->data.data);
		} else {
			printf("Error: Node data at index %d is not of type int\n", index);
		}
		n = n->next;
		index++;
	}
}

void printListString(Node* list) {
	Node* n = list;
	int index = 0;
	while (n != NULL) {
		// print the value the data points to if the data is of type char*
		if (strcmp(n->data.type, "string") == 0) {
			printf("\"%s\" -> ", (char*) n->data.data);
		}
		else {
			printf("Error: Node data at index %d is not of type char*\n", index);
		}
		n = n->next;
		index++;
	}
}

int size(Node* list) {
	Node* n = list;
	int size = 0;
	while (n != NULL) {
		size++;
		n = n->next;
	}
	return size;
}

