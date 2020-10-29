tree_node *parse_input_source_code(FILE *source) {

  stack *main_stack = stack_init();
  stack *aux_stack = stack_init();
  tree_node *root = create_tree_node();

  root->sym.nt = MAINPROGRAM;
  root->sym.is_terminal = false;
  push(main_stack, root); // push start symbol on stack
  TOKEN tkn = get_next_token(source);

  while (true) {
	num_tree_nodes++;
	tree_node *node = (tree_node *)pop(main_stack);
	if ((node != NULL) && (node->sym).is_terminal == true) {
	  if (node->sym.t == EPSILON) {
		  node->token.name = EPSILON;
		  strncpy(node->token.id.str, "epsilon", MAX_LEXEME_LEN);
		continue;
	  }
	  if (node->sym.t != tkn.name) // terminal on top of stack does not match
								   // with lookhead symbol
	  {
		// node->token.name = LEX_ERROR;		
		char *err_msg = (char*) malloc(sizeof(char) * MAX_ERR_TYPE_STR_LEN);
		snprintf(err_msg, MAX_ERR_TYPE_STR_LEN,  "Expected " ANSI_COLOR_YELLOW "\"%s\"," ANSI_COLOR_RESET " Found " ANSI_COLOR_YELLOW "\"%s\" \n" ANSI_COLOR_RESET,terminal_string[node->sym.t], terminal_string[tkn.name]);
		
		store_error(tkn.line_no, SYNTACTIC_ERROR, err_msg);        
		
		printf("Popping token %s from stack top\n",
			   terminal_string[node->sym.t]);
		// tkn = get_next_token(source);
		node = (tree_node *)pop(main_stack);
		if (node == NULL) {
		  store_error(tkn.line_no, SYNTACTIC_ERROR, "Panic Mode Error Recovery Not possible, Partial parse tree formed");          
		  return root;
		}
		continue;
	  } else { // la token and stack top match
		node->token.line_no = tkn.line_no;
		node->token.name = tkn.name;
		switch (tkn.name) {
		case NUM:
		  node->token.num = tkn.num;
		  break;

		case RNUM:
		  node->token.rnum = tkn.rnum;
		  break;

		default:
		  // node->token.id.str = (char *)malloc(sizeof(MAX_LEXEME_LEN));
		  strncpy(node->token.id.str, tkn.id.str, MAX_LEXEME_LEN);
		}
	  }

	  tkn = get_next_token(source);
	  continue;
	}

	if (tkn.name == LEX_ERROR) {
	  store_error(tkn.line_no, LEXICAL_ERROR, tkn.id.str);

	  tkn = get_next_token(source);
	  push(main_stack, node);
	  continue;
	}
	if (node == NULL) {
	  if (tkn.name != DOLLAR) // rule not read completely but stack became empty
	  {
		store_error(tkn.line_no, LEXICAL_ERROR, "Extra symbols in the source code");        
	  } else {
		// printf("\nInput source code is now syntactically correct...........\n\n");
	  }
	  break;
	}

	int rule_no = parse_table[node->sym.nt][tkn.name];
	if (rule_no == NO_MATCHING_RULE) {
	  // printf("[%s][%s]", non_terminal_string[node->sym.nt],
			//  terminal_string[tkn.name]);      
	  store_error(tkn.line_no, LEXICAL_ERROR, "No matching rule found in grammar");  

	  printf("Waiting for an element in follow of " ANSI_COLOR_YELLOW "\"%s\"\n" ANSI_COLOR_RESET, non_terminal_string[node->sym.nt]);
	  
	  while (set_find_elem(follow_set[node->sym.nt], tkn.name) == false) {
		tkn = get_next_token(source);
		if (tkn.name == DOLLAR) {
		  store_error(tkn.line_no, SYNTACTIC_ERROR,  "Panic Mode Error Recovery Not possible, Partial parse tree formed");          
		  return root;
		}
	  }
	  printf("Token \"%s\" found at line number %d\n",
			 terminal_string[tkn.name], tkn.line_no);
	  printf(ANSI_COLOR_GREEN "Resuming parsing\n" ANSI_COLOR_RESET);
	  continue;
	}
	cell rule = grammar[rule_no];
	rhsnode_ptr rhs_ptr = rule.head;

	while (rhs_ptr != NULL) {
	  tree_node *temp = create_tree_node();
	  temp->parent = node;
	  temp->sym = rhs_ptr->sym;
	  add_child(node, temp);
	  push(aux_stack, temp);
	  rhs_ptr = rhs_ptr->next;
	}

	tree_node *temp = (tree_node *)pop(aux_stack);

	while (temp != NULL) {
	  push(main_stack, temp);
	  temp = (tree_node *)pop(aux_stack);
	}
  } // end of while(true) loop : parsing done
  return root;
}
