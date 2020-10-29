#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"


int fast_mod_exp(int a, int b, int m) {
	int res = 1;
	while (b > 0) {
		if (b & 1)
			res = (res * a) % m;
		a = (a * a) % m;
		b >>= 1;
	}
	return res;
}

int hash(char *str) {
	int n = strlen(str);
	int hash_value = 0;
	for (int i = 0; i < n; i++) {
		hash_value += ((str[i] * fast_mod_exp(PRIME, i, HASH_SIZE)) % HASH_SIZE);
	}
	return hash_value % HASH_SIZE;
}

void init_hash_table(hash_table table) {

	if (table == NULL) {
		perror("HASH table allocation error: memory not available\n");
		exit(1);
	}
	for (int i = 0; i < HASH_SIZE; i++) {
		table[i].present = 0;
		table[i].value = NULL;
	}
}

void hash_insert(hash_table table, char *lexeme, int value) {
	int hashValue = hash(lexeme);
	int probe_num = 1;
	while (table[hashValue].present == 1) {
		if(strcmp(lexeme, table[hashValue].lexeme) == 0)	//updating a key's value instead inserting a new one
			break;
		hashValue = (hashValue + probe_num * probe_num) % HASH_SIZE;
		probe_num++;
	}
	strncpy(table[hashValue].lexeme, lexeme, MAX_LEN);
	table[hashValue].present = 1;
	table[hashValue].value = malloc(sizeof(int));
	*(int*)(table[hashValue].value) = value;
}

void hash_insert_ptr_val(hash_table table, char *lexeme, void *value_ptr){
	int hashValue = hash(lexeme);
	int probe_num = 1;
	while (table[hashValue].present == 1) {
		if(strcmp(lexeme, table[hashValue].lexeme) == 0)	//updating a key's value instead inserting a new one
			break;
		hashValue = (hashValue + probe_num * probe_num) % HASH_SIZE;
		probe_num++;
	}
	strncpy(table[hashValue].lexeme, lexeme, MAX_LEN);
	table[hashValue].present = 1;
	table[hashValue].value = value_ptr;
}

int search_hash_table(hash_table table, char *lexeme) {
	int hashValue = hash(lexeme);
	int probe_num = 1;
	while (table[hashValue].present == 1) {
		if (strcmp(table[hashValue].lexeme, lexeme) == 0)
			return *(int*)(table[hashValue].value);
		hashValue = (hashValue + probe_num * probe_num) % HASH_SIZE;
		probe_num++;
	}
	return KEY_NOT_FOUND;
}

bool key_present_in_table(hash_table table, char *lexeme){
	int hashValue = hash(lexeme);
	int probe_num = 1;
	while (table[hashValue].present == 1) {
		if (strcmp(table[hashValue].lexeme, lexeme) == 0)
			return 1;
		hashValue = (hashValue + probe_num * probe_num) % HASH_SIZE;
		probe_num++;
	}
	return 0;
}

void* search_hash_table_ptr_val(hash_table table, char *lexeme){
	if(table == NULL)
		return NULL;
	int hashValue = hash(lexeme);
	int probe_num = 1;
	while (table[hashValue].present == 1) {
		if (strcmp(table[hashValue].lexeme, lexeme) == 0)
			return table[hashValue].value;
		hashValue = (hashValue + probe_num * probe_num) % HASH_SIZE;
		probe_num++;
	}
	return NULL;
}
