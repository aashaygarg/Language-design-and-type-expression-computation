#ifndef HASHTABLE_H
#define HASHTABLE_H

#include<stdlib.h>
#include<stdbool.h>

#define HASH_SIZE 67
#define PRIME 119
#define MAX_LEN 100
#define KEY_NOT_FOUND -1

typedef struct {
	char lexeme[MAX_LEN];
	void *value;
	bool present;
} hash_element;

typedef hash_element hash_table[HASH_SIZE];

int fast_mod_exp(int a, int b, int m);
int hash(char *str);
void init_hash_table(hash_table table);
void hash_insert(hash_table table, char *lexeme, int value);
void hash_insert_ptr_val(hash_table table, char *lexeme, void *value_ptr);
int search_hash_table(hash_table table, char *lexeme);
bool key_present_in_table(hash_table table, char *lexeme);
bool key_present_in_table(hash_table table, char *lexeme);

#endif