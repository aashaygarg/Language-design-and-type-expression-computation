#ifndef GRAMMAR_READ_H
#define GRAMMAR_READ_H

#include<stdlib.h>
#include<stdbool.h>
#include<malloc.h>
#include<math.h>
#include<string.h>
#include "setADT.h"
#include<ctype.h>
#include "hashtable.h"
#include "sourceTokenizer.h"
#include <stdio.h>

#define RHS_MAX_LENGTH 200
#define NO_MATCHING_RULE -1
#define NUM_OF_RULES 49
#define NUM_OF_NONTERMINALS 28
#define NUM_OF_TERMINALS 33
#define MAX_SYMBOL_LENGTH 25
#define SET_SIZE 3

typedef enum
{
MAINPROGRAM,
P_STATEMENTS,
STATEMENTS,
STATEMENT,
DECLARESTMT,
ASSIGNMENTSTMT,
VARDECLIST,
TYPESPEC,
SIMPLEEXPRESSION,
VARDECLID,
TYPESPECIFIER,
RECT_ARR,
JAGGED_ARR,
RANGEDEC,
RANGE,
INDEX,
JAGGED_INDEX_MULTID,
JAGGED_VALUES_INIT,
ROW_VALUES,
COLUMNS,
EXPRESSION,
SUMEXPRESSION,
OREXPRESSION,
ANDEXPRESSION,
MULEXPRESSION,
FACTOR,
SUMOP,
MULOP
} nonterminal;


typedef struct{
    union
    {
        token_name t;
        nonterminal nt;
    };
    bool is_terminal;
} symbol;

typedef struct rhsnode
{
    symbol sym;
    struct rhsnode *next;
} rhsnode;

typedef struct rhsnode *rhsnode_ptr;

typedef struct
{
    nonterminal lhs;
    rhsnode_ptr head;
    rhsnode_ptr tail;
} cell;

cell grammar[NUM_OF_RULES];

hash_table terminal_table;
hash_table non_terminal_table;
hash_element lookup_table[HASH_SIZE];





char lexeme[MAX_LEN];

int lexeme_begin;
int forward_ptr;
int num_of_rounds;
int line_no;

typedef unsigned long long int ull;
typedef ull *set;
int parse_table[NUM_OF_NONTERMINALS][NUM_OF_TERMINALS];
ull first_set[NUM_OF_NONTERMINALS][SET_SIZE];
ull follow_set[NUM_OF_NONTERMINALS][SET_SIZE];

void populate_non_terminal_string();
void populate_terminal_string();
void insert_at_end(rhsnode_ptr *ptr_tail, symbol sym);
symbol get_symbol(char str[]);
void grammar_fill(FILE *fptr);
void print_symbol(symbol sym);
void print_rule(int rule_no);
void print_grammar();
void parser_init() ;

#endif