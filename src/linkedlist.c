#include <stdio.h>
#include <stdlib.h>

void addToList(Node* list, Data data) {
	Node* current = list;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = malloc(sizeof(Node));
	current->next->data = data;
	current->next->next = NULL;
}

void printList(Node *list) {
	Node* current = list;
	while (current != NULL) {
		printf("%s->", current->data.type);
		current = current->next;
	}
	printf("\n");
}