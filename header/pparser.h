#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef P_PARSER_H
#define P_PARSER_H

// parses a file and returns a string containing the contents of the file
char* parseFile(char* filename);

int throwError(char* msg, int* line, int* col, int* errorFlag);

// parse a program:
// <Program> -- > <Function> || <Function> <Program>
int parseProgram(char* str, int* line, int *col, int* pos, int *err);

// parse a function:
//<Function > -- > $function_name '[' <ParamList> ']' '->' <StatementList> 'end_' $function_name
int parseFunction(char* str, int* line, int* col, int* pos, int *err);

// parse a parameter list:
//end = 1 if end ']' should be parsed
//end = 0 if end ']' should not be parsed
int parseParamList(char* str, int* line, int* col, int* pos, int *err, int end);

// parse a parameter list:
//TODO LATER
int parseStatementList(char* str, int* line, int* col, int* pos, int *err);

// parses white space
// str is the current string to scan
// pos is the position in the string (may be updated)
// n = 0 for no new line
// n = 1 for new line
void parseWhiteSpace(char* str, int* line, int* col, int* pos, int n);

// parses a variable name
// str is the current string to scan
// pos is the position in the string (may be updated)
// returns false if parsing was not successful
// returns true if parsing was successful
int parseVariable(char* str, int* col, int* pos);

// parses a number
// str is the current string to scan
// pos is the position in the string (may be updated)
// res will contain the parsed integer (if n = 0)  if no integer, then res = -1
// resf will contain the parsed float (if n = 1) if no float, then resf = -1.0
// returns 0 if parsing was not successful
// returns 1 if number was parsed was an integer
// returns 2 if number parsed was a float
int parseNumber(char* str, int* col, int* pos, int *res, float *resf);

// looks ahead in the string to see if the next character
// matches the specified character
int peek(char* str, int* pos, char c);

// scans a specific string
// str is the current string to scan
// pos is the position in the string (may be updated)
// c is the string to be matched
int eat(char* str, int* col, int* pos, char* s);

// scans a specific string
// str is the current string to scan
// pos is the position in the string (may be updated)
// c is the character to be matched
int eatChar(char* str, int* col, int* pos, char c);

// forms a substring from a string with the given lower and upper indices
char* substr(char* str, int lower, int upper);

#endif
