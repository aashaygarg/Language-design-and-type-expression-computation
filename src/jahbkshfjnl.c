
/*************************************************************************************************************************/

//Functions to create and print parse tree

ParseTree*  parseInputSourceCode(char *testcaseFile, ParsingTable* table, int* syntax_errors){

	/**********************************************************************/

							//INITIALIZATION PHASE

	//Initialize_lexer
	FILE* fp = initialize_lexer(testcaseFile);

	if(fp == NULL){
		printf("\nFile not opened for parsing\n");
		return NULL;
	}

	printf("\n\n------------------------------LEXER INITIALIZED--------------------------\n\n");

	//Initializing ParseTree
	ParseTree* tree = initialize_tree();

	//Making Start symbol as the root of parse tree
	add_root(tree);
	printf("\n\n------------------------------TREE INITIALIZED---------------------------\n\n");


	//Initializing Stack
	Stack* stack = initialize_stack();

	//Pushing $ and starting nonterminal on the stack
	TreeNode* dollar_node =  create_node(0,	DOLLAR, NULL);

	push(stack,dollar_node);
	push(stack,tree->root);

	printf("\n\n------------------------------STACK INITIALIZED--------------------------\n\n");

	printf("\n\nStart obtaining tokens from lexer and parse them\n\n");

	/****************************************************************************/
								//Parsing Phase Begins

	Tokentype lookahead;

	//Initially get a token from the file
	Token* new_token = getNextToken(&fp);


	//If first token received is NULL
	if(new_token==NULL){
		printf("\n\nInput File Empty\n\n");
		return NULL;			
	}

	
	int error_detect = 0;
	


	while(1){

		//If input is consumed
		if(new_token==NULL){

			//If input consumed
			if(isTopDOLLAR(stack) && error_detect!=1){
				printf("\n\n---------------------STACK EMPTY AND INPUT CONSUMED------------------------\n\n");
				printf("\n\n------Input source code is syntactically CORRECT - PARSING SUCCESSFUL-----------------\n\n");
			}
			else{
				*syntax_errors = 1;
				printf("\n\n------Input source code is syntactically WRONG - PARSING NOT SUCCESSFUL---------------\n\n");
			}

			break;
		}

		
		//Otherwise get the lookahead symbol
		lookahead = new_token->type;
				

		if(lookahead==ERROR){
			//Skip Lexical Error
			*syntax_errors=1;
			new_token= getNextToken(&fp);
			continue;
		}



		//If top of the stack is $ and input is still left
		if(isTopDOLLAR(stack)){
			*syntax_errors = 1;
			printf("\n\nUnexpected tokens at the end - Stack empty but program still left\n\n");
			printf("\n\n------Input source code is syntactically WRONG - PARSING NOT SUCCESSFUL---------------\n\n");
			break;
		}


		//POP the symbol on the top of the stack
		StackNode* stk_node = pop(stack);
		TreeNode* tree_node = stk_node->treeNodePointer;

		
		//Terminal
		if(tree_node->info->term_or_nonterm==0){

			//Symbol on the stack matches with the lookahead symbol
			if(lookahead == tree_node->info->type.terminal){

				//Will help in printing the parse tree
				tree_node->lexicalTOKEN = new_token;

				//Get next Lookahead Symbol
				new_token = getNextToken(&fp);
				continue;			
							
			}

			//If lookahead and top of stack don't match

			/******************************************************** Panic Recovery Mode *************************************************/

			else{

				
				//Report Error
				error_detect = 1;
				*syntax_errors = 1;
				printf("Line No: %d, Syntax error: The token  for lexeme %s does not match at line %d\n",new_token->line_no,new_token->lexeme,new_token->line_no);

				//error recovery	

				StackNode* stk_node2 = top(stack);
				TreeNode* tree_node2 = stk_node2->treeNodePointer;


				//Skip lookahead symbols until something matches
				while(new_token!=NULL){

					lookahead = new_token->type;

					//Check for the current one 
					if(lookahead == tree_node->info->type.terminal){
						push(stack, tree_node);
						break;
					}

					
					//Check for the following one

					//If terminal
					if(tree_node2->info->term_or_nonterm==0){
						if(lookahead == tree_node2->info->type.terminal){
							break;
						}
					}
					else{
						Cell* to_be_applied_rule2 = table->cells[tree_node2->info->type.nonterminal][lookahead];
						if(to_be_applied_rule2!=NULL){
							break;
						}
					}
					
					
					if(new_token->type==SEMICOLON){
						new_token = getNextToken(&fp);
						break;
					}
					

					new_token = getNextToken(&fp);
					
				}
		
				continue;			

			}

			/******************************************************** Panic Mode Over ***************************************************/			
		}			
		

		//if top of the stack is a non terminal
		else{

			//Get the rule to be applied from the parsing table
			Cell* to_be_applied_rule = table->cells[tree_node->info->type.nonterminal][lookahead];


			//If no rule matches

			/******************************************************** Panic Recovery Mode *************************************************/

			if(to_be_applied_rule == NULL){

				//Report Error
				error_detect = 1;
				*syntax_errors = 1;
				printf("Line No: %d, Syntax error: The token  for lexeme %s does not match at line %d\n",new_token->line_no,new_token->lexeme,new_token->line_no);



				//error recovery	

				StackNode* stk_node2 = top(stack);
				TreeNode* tree_node2 = stk_node2->treeNodePointer;

				//Skip lookahead symbols until something matches
				while(new_token!=NULL){

					lookahead = new_token->type;

					//Check for the current one 
					Cell* to_be_applied_rule1 = table->cells[tree_node->info->type.nonterminal][lookahead];


					if(to_be_applied_rule1!=NULL){
						//Push it on the stack and start the iteration all over
						push(stack, tree_node);
						break;
					}

					//Check for the following one

					//If terminal
					if(tree_node2->info->term_or_nonterm==0){
						if(lookahead == tree_node2->info->type.terminal){
							break;
						}
					
						else{
							Cell* to_be_applied_rule2 = table->cells[tree_node2->info->type.nonterminal][lookahead];
							if(to_be_applied_rule2!=NULL){
								break;
							}
						}
					}

					
					if(new_token->type==SEMICOLON){
						new_token = getNextToken(&fp);
						break;
					}
					


					new_token = getNextToken(&fp);
					
				}
				
			}

			/******************************************************** Panic Mode Over ***************************************************/


			//Normal Case
			else{				
				//Add Children to the parse tree for the popped non terminal from the stack
				add_children(tree_node, to_be_applied_rule->rule);

				//PUSH RHS of the rule on the top of the stack
				push_children_on_the_stack(stack,tree_node);
			}		

		}

		//Go to begin of the while loop
	}

	if(fp!=NULL)
		fclose(fp);

	return tree;

}


