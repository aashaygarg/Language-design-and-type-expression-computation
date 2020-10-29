#ifndef STK_H
#define STK_H

#include "hashtable.h"
#include "driver.h"


hash_element lookup_table[HASH_SIZE];

typedef enum {
PROGRAM,
SQ_O,
SQ_C,
CURL_O,
CURL_C,
DECLARE,
ID,
NUM, 
SEMICOLON,
COLON,
LIST,
OF,
VARIABLES,
INTEGER,
REAL,
BOOLEAN,
ARRAY,
JAGGED,
ASSIGNOP,
RANGEOP,
PLUS,
MINUS,
MUL,
DIV,
AND,
OR,
SIZE,
RB_O,
RB_C,
EPSILON,
VALUES,
R_ONE,
DOLLAR
} token_name;

typedef struct token {
  token_name name;
 
  union {
	char str[MAX_LEN];
	int num;
  } id;
 
  int line_no;
} ELEMENT;

typedef struct node{
	ELEMENT ele;
	struct node * next;
} NODE;

typedef struct {
  NODE* head;
  NODE* tail;
} tokenStream;



ELEMENT get_next_token(FILE *fp);
void tokeniseSourcecode(char *str, tokenStream *s);
void populate_lookup_table();
token_name search_lookup_table(char *lexeme);

#endif