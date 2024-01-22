#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

#ifndef P_MANAGER_H
#define P_MANAGER_H

// adds a new function to the program
// takes in the function name, the number of parameters, and the parameters
Node* createNewFunction(char* fName, int paramc, char* fparamss[]);

void DeleteFunction(Node* function);

void PrintFunction(Node* function);

void PrintProgram(Node* program);

void DeleteProgram(Node* program);

void addFunctionToProg(Node** program, Node* newFunction);

#endif