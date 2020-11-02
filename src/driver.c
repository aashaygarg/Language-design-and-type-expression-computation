/***************************************
Group No 35
 2018A7PS0238P Name: Hritwik Goklaney		         
 2018A7PS0262P Name: Yash Gupta 
 2018A7PS0161P Name: Chaitanya Kulkarni		         
 2018A7PS0004P Name: Aashay Garg	
***************************************/


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

        char *str = (char*)malloc(100*sizeof(char));
        printf("Enter name of test case file: ");
        gets(str);
        readGrammar();
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

        while(true){
            printf("Enter option number: ");
            scanf("%d", &i);
            if(i==0)
                return;
            else if(i==1){
                createParseTree(tk_s_ptr);
            }
            else if(i==2){
                printf("Not yet implemented successfully");
            }
            else if(i==3){
                printParseTree(ptr);
                if (ptr == NULL){
                    printf("Empty parse tree\n");
                }
            }
            else if(i==4){
                traverseParseTree(ptr);
            }
            else{
                printf("Option number is invalid");
            }
        }

	


	return 0;
}


