#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// structure for Data element
typedef struct Data {
	char* type;
	void* data;
} Data;

// structure for a node in a linked list
typedef struct Node {
	Data data;
	struct Node* next;
} Node;

// adds a Data element to the end of the list
void addToList(Node** list, Data data);

// removes a Data element from the end of the list
void removeFromList(Node** list);

// adds a Data element to specified index of the list
// index = size-1 if back of the list
// index = 0 if front of the list
// where size is the number of elements in the list
void addToListIndex(Node** list, int index, Data data);

// removes a Data element from a specified index of the list
// index = size-1 if back of the list
// index = 0 if front of the list
// where size is the number of elements in the list
void removeFromListIndex(Node** list, int index);

// prints the int values of the list (assuming the list contains ints)
void printListInt(Node* list);

// prints the string values of the list (assuming the list contains strings)
void printListString(Node* list);

// counts the size of the list (number of elements or nodes)
int size(Node* list);

// returns the Data element at the specified index
// or NULL if index is out of bounds
Data* get(Node* list, int index);

#endif
