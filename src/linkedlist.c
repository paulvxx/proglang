#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"


void addToList(Node** list, Data data) {
	if (*list == NULL) {
		*list = malloc(sizeof(Node));
		(*list)->data = data;
		(*list)->next = NULL;
	} else {
		Node *n = malloc(sizeof(Node));
		n->data = data;
		n->next = NULL;
		(*list)->next = n;
	}
}

void printListInt(Node* list) {
	Node* n = list;
	int index = 0;
	while (n != NULL) {
		if (strcmp(n->data.type, "int")==0) {
			printf("%d -> ", *(int*)n->data.data);
		} else {
			printf("Error: Node data at index %d is not of type int\n", index);
		}
		n = n->next;
		index++;
	}
}
