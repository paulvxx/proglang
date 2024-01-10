#include <stdio.h>
#include <stdlib.h>

int main(int argc, char argv[]) {
	Node* n = malloc(sizeof(int));
	int x = 5;
	void* v = &x;
	n->data = v;
	n->type = "Int";
	printList(n);
	return 0;
}