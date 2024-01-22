#define FALSE 0
#define TRUE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pparser.h"
#include "programmanager.h"
#include "error.h"


char* parseFile(char* filename) {
    FILE* fp;
    char lineBuffer[1024]; // Buffer for each line
    size_t capacity = 1024;
    char* result = malloc(capacity);
    if (result == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    result[0] = '\0';

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    while (fgets(lineBuffer, sizeof(lineBuffer), fp) != NULL) {
        size_t newLength = strlen(result) + strlen(lineBuffer) + 1;
        if (newLength > capacity) {
            capacity = newLength;
            char* temp = realloc(result, capacity);
            if (temp == NULL) {
                free(result);
                perror("realloc failed");
                exit(EXIT_FAILURE);
            }
            result = temp;
        }
        strcat(result, lineBuffer);
    }

    fclose(fp);
    return result;
}

// throws an error
int throwError(char* msg, int *line, int *col, int* errorFlag) {
    if (*errorFlag) {
        ERROR("%s, line=%d, col=%d\n", msg, *line, *col);
        exit(-1);
        // Set the error flag to false to stop printing errors
        *errorFlag = FALSE;
    }
    return FALSE;
}


// parse a program:
//<Program> -- > <Function> || <Function> <Program>
int parseProgram(char* str, int* line, int* col, int* pos, int* err, Node** program) {
    parseWhiteSpace(str, line, col, pos, 1);
    if (!parseFunction(str, line, col, pos, err, program)) return FALSE; //generateError("idk", lineno, *pos, "Function name required."); // return FALSE;
    parseWhiteSpace(str, line, col, pos, 1);
    if (strlen(str) != *pos) {
        if (!parseProgram(str, line, col, pos, err, program)) return FALSE;
    }
    return TRUE;
}

// parse a function:
// <Function> -- > $function_name '[' <ParamList> ']' '->' <StatementList> 'end_' $function_name
int parseFunction(char* str, int* line, int* col, int* pos, int *err, Node** program) {
    int oldpos = *pos;
    parseVariable(str, col, pos);
    if (oldpos == *pos) return throwError("Syntax Error: Expected function name", line, col, err);
    //(*col) = *col + (*pos - oldpos);
    char *varname = substr(str, oldpos, *pos);
    parseWhiteSpace(str, line, col, pos, 1);
    if (!eatChar(str, col, pos, '[')) return throwError("Syntax Error: Expected '['", line, col, err);
    parseWhiteSpace(str, line, col, pos, 1);
    int pcount = 0;
    char** params = NULL;
    if (!parseParamList(str, line, col, pos, err, TRUE, program, &params, &pcount)) return FALSE;
    /////////////////////////////////////////
    Node* func = createNewFunction(varname, pcount, params);
    // free the parameter list
    for (int i = 0; i < pcount; i++) {
		free(params[i]);
	}
	free(params);
    /////////////////////////////////////////
    if (!eatChar(str, col, pos, ']')) return throwError("Syntax Error: Expected ']'", line, col, err);
    parseWhiteSpace(str, line, col, pos, 0);
    if (!eat(str, col, pos, "->")) return throwError("Syntax Error: Expected '->'", line, col, err);
    parseWhiteSpace(str, line, col, pos, 1);
	if (!parseStatementList(str, line, col, pos, err, program)) return FALSE;
    parseWhiteSpace(str, line, col, pos, 0);
    if (!eat(str, col, pos, "end_")) return throwError("Syntax Error: Expected 'end_'", line, col, err);
    if (!eat(str, col, pos, varname)) return throwError("Syntax Error: Expected function name", line, col, err);
    free(varname);
    // add the function to the program
    addFunctionToProg(program, func);
    //
    return TRUE;
}

// parse a parameter list:
int parseParamList(char* str, int* line, int* col, int* pos, int* err, int end, Node** program, char*** paramList, int* params) {
    parseWhiteSpace(str, line, col, pos, 1);
    if (end && peek(str, pos, ']')) return TRUE;
    // parse the list of parameters
    // the @ symbol is used to denote variables that are passed by reference
    else if (peek(str, pos, '@')) {
		(*pos)++;
	}
    int oldPos = *pos;
    if (!parseVariable(str, col, pos)) return FALSE;
    /////////////////////////////////////////
    // get the substring of the parameter name
    char* p = substr(str, oldPos, *pos);
    (*params)++;
    // realloc the paramList array dynamically
    *paramList = realloc(*paramList, sizeof(char*) * (*params + 1));
    (*paramList)[(*params) - 1] = p;
    /////////////////////////////////////////

    parseWhiteSpace(str, line, col, pos, 1);
    if (peek(str, pos, ',')) {
		eatChar(str, col, pos, ',');
		if (!parseParamList(str, line, col, pos, err, FALSE, program, paramList, params)) return FALSE;
	}
	return TRUE;
}

// TODO LATER
int parseStatementList(char* str, int* line, int* col, int* pos, int* err, Node** program) {
    return TRUE;
}


void parseWhiteSpace(char* str, int* line, int* col, int* pos, int n) {
    // newlines allowed
    if (n) {
        while ( ((*pos) < strlen(str)) && (str[*pos] == ' ' || str[*pos] == '\t' || str[*pos] == '\n')) {
            if (str[*pos] == '\n') {
                (*line)++;
                col = 0;
            }
			else {
				(*col)++;
			}
            (*pos)++;
        }
     // no newlines allowed
    } else {
		while (str[*pos] == ' ' || str[*pos] == '\t') {
			(*pos)++;
            (*col)++;
		}
	}
}

int parseVariable(char* str, int* col, int* pos) {
    // leave it up to caller to obtain substring
    // variable name must start with a letter
    if (((*pos) < strlen(str)) && (str[*pos] - 65) >= 0 && (90 - str[*pos]) >= 0) {
        (*pos)++;
        (*col)++;
    } else if (((*pos) < strlen(str)) && (str[*pos] - 97) >= 0 && (122 - str[*pos]) >= 0) {
        (*pos)++;
        (*col)++;
    }
    else {
        return 0;
    }
    // variable name can contain letters, numbers, and underscores
    while (((*pos) < strlen(str)) && (str[*pos] - 65) >= 0 && (90 - str[*pos]) >= 0 ||
        (str[*pos] - 97) >= 0 && (122 - str[*pos]) >= 0 || 
        (str[*pos] - 48) >= 0 && (57 - str[*pos]) >= 0 ||
        str[*pos] == '_'
        ) { (*pos)++; (*col)++; }
    return 1;
}

int parseNumber(char* str, int* col, int* pos, int* res, float* resf) {
    // double 0's are not allowed e.g. "00" 
    *res = -1;
    *resf = -1.0;
    if (((*pos) >= strlen(str)) || !((str[*pos] - 48) >= 0 && (57 - str[*pos]) >= 0)) {
        return 0;
    }
    else if ((((*pos) + 1) < strlen(str)) && str[*pos] == '0' && str[*pos + 1] == '0') {
        return 0;
    }

    *res = 0;
    *resf = 0.0;
    //printf("%d,%d,%d\n", *pos, strlen(str), str[*pos]);
    while (((*pos) < strlen(str)) && (str[*pos] - 48) >= 0 && (57 - str[*pos]) >= 0) {
        *res = *res * 10 + (str[*pos] - 48);
        *resf = *resf * 10 + (str[*pos] - 48);
        (*pos)++;
        (*col)++;
    }

    if (eat(str, col, pos, ".")) {
        int decimal = 0;
        float decimalf = 0.0;
        int count = 0;
        while (((*pos) < strlen(str)) && (str[*pos] - 48) >= 0 && (57 - str[*pos]) >= 0) {
            decimal = decimal * 10 + (str[*pos] - 48);
            decimalf = decimalf * 10 + (str[*pos] - 48);
            (*pos)++;
            (*col)++;
            count++;
        }
        while (count > 0) {
            decimalf /= 10;
            count--;
        }
        *resf += decimalf;
        return 2;
    }
    return 1;
}

int peek(char* str, int* pos, char c) {
    if (*pos >= strlen(str) || str[*pos] != c) return FALSE;
    return TRUE;
}

int eat(char* str, int* col, int* pos, char* s) {
    if (*pos >= strlen(str)) return FALSE;
    int i = 0;
    while (i < strlen(s)) {
		if (!eatChar(str, col, pos, s[i])) return FALSE;
		i++;
	}
    if (i != strlen(s)) return FALSE;
	return TRUE;
}

int eatChar(char* str, int* col, int* pos, char c) {
	if (*pos >= strlen(str) || str[*pos] != c) return FALSE;
	(*pos)++;
    (*col)++;
	return TRUE;
}
