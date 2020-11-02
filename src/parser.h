#ifndef PARSER_H
#define PARSER_H

#include "grammar_read.h"
#include "Tree.h"
#include <stdio.h>

extern char non_terminal_string[NUM_OF_NONTERMINALS][MAX_SYMBOL_LENGTH];



int rightmost_set_bit(unsigned long long *num);

void create_parse_table();

void populate_first_sets();

void populate_follow_sets();

void print_parse_table();

void printParseTree(tree_node *root);

void traverseParseTree(tree_node *root);

tree_node *createParseTree(tokenStream *tk_s_ptr);

ull *get_rule_first_set(rhsnode_ptr node);

bool is_superset(ull a[SET_SIZE], ull b[SET_SIZE]);

#endif
