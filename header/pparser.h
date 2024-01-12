#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"

// parses a file and returns a string containing the contents of the file
char* parseFile(char* filename);


// parse a program:
// <Program> -- > <Function> || <Function> <Program>
int parseProgram(char* str, int* pos);

// parse a function:
//<Function > -- > $function_name '[' <ParamList> ']' '->' <StatementList> 'end_' $function_name
int parseFunction(char* str, int* pos);

// parse a parameter list:
//TODO LATER
int parseParamList(char* str, int* pos);

// parse a parameter list:
//TODO LATER
int parseStatementList(char* str, int* pos);

// parses white space
// str is the current string to scan
// pos is the position in the string (may be updated)
// n = 0 for no new line
// n = 1 for new line
void parseWhiteSpace(char* str, int* pos, int n);

// parses a variable name
// str is the current string to scan
// pos is the position in the string (may be updated)
// n = 0 for no new line
// n = 1 for new line
void* parseVariable(char* str, int* pos);

// parses a number
// str is the current string to scan
// pos is the position in the string (may be updated)
// res will contain the parsed integer (if n = 0)  if no integer, then res = -1
// resf will contain the parsed float (if n = 1) if no float, then resf = -1.0
// n = 0 if scanning for integer only
// n = 1 if scanning for float
void* parseNumber(char* str, int* pos, int *res, float *resf, int* n);

// scans a specific string
// str is the current string to scan
// pos is the position in the string (may be updated)
// c is the string to be matched
int eat(char* str, int* pos, char* c);

// scans a specific string
// str is the current string to scan
// pos is the position in the string (may be updated)
// c is the character to be matched
int eatChar(char* str, int* pos, char c);

// forms a substring from a string with the given lower and upper indices
char* substr(char* str, int lower, int upper);