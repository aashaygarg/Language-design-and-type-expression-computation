#ifndef DRIVER_H
#define DRIVER_H

#include<stdio.h>


#define NUM_OF_RULES 64
#define NUM_OF_NONTERMINALS 40
#define NUM_OF_TERMINALS 33
#define MAX_SYMBOL_LENGTH 25


char terminal_string[NUM_OF_TERMINALS][MAX_SYMBOL_LENGTH];
char non_terminal_string[NUM_OF_NONTERMINALS][MAX_SYMBOL_LENGTH];


FILE *parse_tree_file_ptr;

int num_tree_nodes;


#endif