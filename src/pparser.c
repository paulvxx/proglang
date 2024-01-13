#define FALSE 0
#define TRUE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pparser.h"
#include "error.h"

static int lineno = 1;

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

// parse a program:
//<Program> -- > <Function> || <Function> <Program>
int parseProgram(char* str, int* pos) {
    parseWhiteSpace(str, pos, 1);
    if (!parseFunction(str, pos)) return FALSE; //generateError("idk", lineno, *pos, "Function name required."); // return FALSE;
    parseWhiteSpace(str, pos, 1);
    if (strlen(str) != *pos) {
        if (!parseProgram(str, pos)) return FALSE;
    }
    return TRUE;
}

// parse a function:
// <Function> -- > $function_name '[' <ParamList> ']' '->' <StatementList> 'end_' $function_name
int parseFunction(char* str, int* pos) {
    int oldpos = *pos;
    parseVariable(str, pos);
    if (oldpos == *pos) return FALSE;
    char *varname = substr(str, oldpos, *pos);
    parseWhiteSpace(str, pos, 1);
    if (!eatChar(str, pos, '[')) return FALSE;
    parseWhiteSpace(str, pos, 1);
    if (!parseParamList(str, pos, TRUE)) return FALSE;
    //parseWhiteSpace(str, pos, 1);
    if (!eatChar(str, pos, ']')) return FALSE;
    parseWhiteSpace(str, pos, 0);
    if (!eat(str, pos, "->")) return FALSE;
    parseWhiteSpace(str, pos, 1);
	if (!parseStatementList(str, pos)) return FALSE;
    parseWhiteSpace(str, pos, 0);
    if (!eat(str, pos, "end_")) return FALSE;
    if (!eat(str, pos, varname)) return FALSE;
    free(varname);
    return TRUE;
}

// parse a parameter list:
int parseParamList(char* str, int* pos, int end) {
    parseWhiteSpace(str, pos, 1);
    if (end && peek(str, pos, ']')) return TRUE;
    // parse the list of parameters
    // the @ symbol is used to denote variables that are passed by reference
    else if (peek(str, pos, '@')) {
		(*pos)++;
	}
    if (!parseVariable(str, pos)) return FALSE;
    parseWhiteSpace(str, pos, 1);
    if (peek(str, pos, ',')) {
		(*pos)++;
		if (!parseParamList(str, pos, FALSE)) return FALSE;
	}
	return TRUE;
}

// TODO LATER
int parseStatementList(char* str, int* pos) {
    return TRUE;
}


void parseWhiteSpace(char* str, int* pos, int n) {
    // newlines allowed
    if (n) {
        while ( ((*pos) < strlen(str)) && str[*pos] == ' ' || str[*pos] == '\t' || str[*pos] == '\n') {
            if (str[*pos] == '\n') lineno++;
            (*pos)++;
        }
     // no newlines allowed
    } else {
		while (str[*pos] == ' ' || str[*pos] == '\t') {
			(*pos)++;
		}
	}
}

int parseVariable(char* str, int* pos) {
    // leave it up to caller to obtain substring
    // variable name must start with a letter
    if (((*pos) < strlen(str)) && (str[*pos] - 65) >= 0 && (90 - str[*pos]) >= 0) {
        (*pos)++;
    } else if (((*pos) < strlen(str)) && (str[*pos] - 97) >= 0 && (122 - str[*pos]) >= 0) {
        (*pos)++;
    }
    else {
        return 0;
    }
    // variable name can contain letters, numbers, and underscores
    while (((*pos) < strlen(str)) && (str[*pos] - 65) >= 0 && (90 - str[*pos]) >= 0 ||
        (str[*pos] - 97) >= 0 && (122 - str[*pos]) >= 0 || 
        (str[*pos] - 48) >= 0 && (57 - str[*pos]) >= 0 ||
        str[*pos] == '_'
        ) (*pos)++;
    return 1;
}

int parseNumber(char* str, int* pos, int* res, float* resf) {
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
    }

    if (((*pos) < strlen(str)) && str[*pos] == '.') {
        (*pos)++;
        int decimal = 0;
        float decimalf = 0.0;
        int count = 0;
        while (((*pos) < strlen(str)) && (str[*pos] - 48) >= 0 && (57 - str[*pos]) >= 0) {
            decimal = decimal * 10 + (str[*pos] - 48);
            decimalf = decimalf * 10 + (str[*pos] - 48);
            (*pos)++;
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

int eat(char* str, int* pos, char* s) {
    if (*pos >= strlen(str)) return FALSE;
    int i = 0;
    while (i < strlen(s)) {
		if (!eatChar(str, pos, s[i])) return FALSE;
		i++;
	}
    if (i != strlen(s)) return FALSE;
	return TRUE;
}

int eatChar(char* str, int* pos, char c) {
	if (*pos >= strlen(str) || str[*pos] != c) return FALSE;
	(*pos)++;
	return TRUE;
}

char* substr(char* str, int lower, int upper) {
    if (lower < 0 || upper > strlen(str) || 
        lower > strlen(str) || upper < 0) {
		return NULL;
	}
    // allocate memory for the substring
	char* result = malloc(sizeof(char) * (upper - lower + 1));
    // improper bounds
	if (result == NULL) {
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
    // form the substring
	int i = 0;
	while (lower < upper) {
		result[i] = str[lower];
		i++;
		lower++;
	}
	result[i] = '\0';
	return result;
}