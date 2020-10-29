#include "driver.h"
#include "parser.h"
#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammar_read.h"

int num_tree_nodes;

int main()
{
        FILE *fptr = fopen("Grammar_PPL.txt", "r");
        char *str = (char*)malloc(100*sizeof(char));
        strcpy(str,"t1.txt");
        
        if(fptr == NULL)
            {
                perror("fopen");
            }
            
        populate_non_terminal_string();
        populate_terminal_string();
        parser_init();
        grammar_fill(fptr);
        print_grammar();
        
        tokenStream tk_s;
        tk_s.head=NULL;
        tk_s.tail=NULL;
        tokenStream *tk_s_ptr = &tk_s;
        tokeniseSourcecode(str, tk_s_ptr);
        
        int i=0;
        NODE* tt = tk_s_ptr->head;
        while(tt!=NULL){
            i++;
            printf("%d\n",tt->ele.name);
            tt=tt->next;
        }


        populate_first_sets();
        
        populate_follow_sets();


        create_parse_table();
        print_parse_table();
        
        tree_node *ptr = parse_input_source_code(tk_s_ptr);
   
	if (ptr == NULL) 
	{
		printf("Empty parse tree\n");
	}
				
	print_parse_tree(ptr);			
	fclose(fptr);
        

	return 0;
}


