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

void removeFromList(Node** list) {
	if (*list == NULL) return;
	if ((*list)->next == NULL) {
		free(*list);
		*list = NULL;
		return;
	}
	else {
		Node* n = *list;
		while (n->next->next != NULL) {
			n = n->next;
		}
		free(n->next);
		n->next = NULL;
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

void removeFromListIndex(Node** list, int index) {
	if (index == size(*list) - 1) removeFromList(list);
	else if (index == 0) {
		Node* n = *list;
		*list = (*list)->next;
		free(n);
	} else {
		Node* n = *list;
		int i = 0;
		while (i < (index - 1)) {
			n = n->next;
			i++;
		}
		Node* toRemove = n->next;
		n->next = n->next->next;
		free(toRemove);
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

Data* get(Node* list, int index) {
	if (size(list) <= index || index < 0) return NULL;
	Node* n = list;
	int i = 0;
	while (i < index) {
		n = n->next;
		i++;
	}
	return &(n->data);
}