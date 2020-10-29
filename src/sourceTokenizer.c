#include "sourceTokenizer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>



void tokeniseSourcecode(char *str, tokenStream *s)
{

	FILE* fptr = fopen(str, "r");
	if (fptr == NULL) {
		printf("Could not open file %s", str);
		return false;
	}
	
	populate_lookup_table();
	int line_no = 0;
	char buffer[MAX_LEN];

	while (fgets(buffer, sizeof(buffer), fptr) != NULL) {

		char *line_read;
		int i;
		line_read= strtok(buffer, " \n");
		for (i = 0; line_read != NULL; i++) {
		  if(s->head == NULL){
			NODE* ptr = (NODE*)malloc(sizeof(NODE));
			ptr->ele.name = search_lookup_table(line_read);

		
			switch(ptr->ele.name){
				case ID : strcpy(ptr->ele.id.str, line_read);
		                      break;
				case NUM : ptr->ele.id.num = atoi(line_read);
		                       break;
        		}
  
			ptr->ele.line_no = line_no;
			ptr->next=NULL;
			s->head = ptr;
			s->tail = ptr;

	  }
	  else{

		NODE* ptr = (NODE*)malloc(sizeof(NODE));
		ptr->ele.name = search_lookup_table(line_read);
		switch(ptr->ele.name){
			case ID : strcpy(ptr->ele.id.str, line_read);
                              break;
			case NUM : ptr->ele.id.num = atoi(line_read);
                               break;
            
            }
    
		ptr->ele.line_no = line_no;
		ptr->next=NULL;

	  s->tail->next=ptr;
	  s->tail = ptr;

	}

	  line_read = strtok(NULL, " \n");
    
	}
	line_no++;
  }
//printf("%d",line_no);
}


void populate_lookup_table() {

  hash_insert(lookup_table, "[", SQ_O);
  hash_insert(lookup_table, "]", SQ_C);
  hash_insert(lookup_table, "{", CURL_O);
  hash_insert(lookup_table, "}", CURL_C);
  hash_insert(lookup_table, "(", RB_O);
  hash_insert(lookup_table, ")", RB_C);
  hash_insert(lookup_table, ":", COLON);
  hash_insert(lookup_table, ";", SEMICOLON);
  hash_insert(lookup_table, "integer", INTEGER);
  hash_insert(lookup_table, "real", REAL);
  hash_insert(lookup_table, "boolean", BOOLEAN);
  hash_insert(lookup_table, "declare", DECLARE);
  hash_insert(lookup_table, "list", LIST);
  hash_insert(lookup_table, "of", OF);
  hash_insert(lookup_table, "variables", VARIABLES);
  hash_insert(lookup_table, "program", PROGRAM);
  hash_insert(lookup_table, "&&&", AND);
  hash_insert(lookup_table, "|||", OR);
  hash_insert(lookup_table, "+", PLUS);
  hash_insert(lookup_table, "-", MINUS);
  hash_insert(lookup_table, "*", MUL);
  hash_insert(lookup_table, "/", DIV);
  hash_insert(lookup_table, "=", ASSIGNOP);
  hash_insert(lookup_table, "..", RANGEOP);
  hash_insert(lookup_table, "jagged", JAGGED);
  hash_insert(lookup_table, "array", ARRAY);
  hash_insert(lookup_table, "size", SIZE);
  hash_insert(lookup_table, "R1", R_ONE);

}


token_name search_lookup_table(char *lexeme) {
  token_name num = search_hash_table(lookup_table, lexeme);
  if (KEY_NOT_FOUND == num) {

     for(int i=0;i<strlen(lexeme);i++)
      {
      if (!isdigit(lexeme[i])){
        return ID;
       }
      }
      return NUM;
   
  }
  return num;
}
