/***************************************
Group No 35
 2018A7PS0238P Name: Hritwik Goklaney		         
 2018A7PS0262P Name: Yash Gupta 
 2018A7PS0161P Name: Chaitanya Kulkarni		         
 2018A7PS0004P Name: Aashay Garg	
***************************************/
#include "parser.h"
#include "hashtable.h"
#include "setADT.h"
#include "Stack.h"
#include <ctype.h>
#include <malloc.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COLUMN_SIZE 20

int rightmost_set_bit(ull *num) {
  ull temp = (*num & (*num - 1));
  int pos = ULL_NUM_BITS - 1 - log2(temp ^ *num);
  *num = temp;
  return pos;
}


void create_parse_table() {
  for (int i = 0; i < NUM_OF_RULES; i++) {
	// printf("Filling r")
	nonterminal nt = grammar[i].lhs;
	set rhs_first_set = get_rule_first_set(grammar[i].head);

	for (int j = 0; j < SET_SIZE; j++) {
	  ull num = rhs_first_set[j]; 

	  while (num) {
		int pos = rightmost_set_bit(&num); 
		pos += (ULL_NUM_BITS * j);
		if (EPSILON == pos) {
		  for (int j = 0; j < SET_SIZE; j++) {
			ull num =follow_set[nt][j]; 
			while (num) {
			  int pos = rightmost_set_bit(&num);
			  pos += (ULL_NUM_BITS * j);
			  if (EPSILON != pos) {
				parse_table[nt][pos] = i;
			  }
			}
		  } 
		}  
		else {
		  parse_table[nt][pos] = i; 
		}
	  } 
	}   
  }     
}

tree_node *createParseTree(tokenStream *tk_s_ptr) {

  stack *main_stack = stack_init();
  stack *aux_stack = stack_init();
  tree_node *root = create_tree_node();
  NODE* ptrr = tk_s_ptr->head;

  root->sym.nt = MAINPROGRAM;
  root->sym.is_terminal = false;
  push(main_stack, root); 
  ELEMENT tkn = ptrr->ele;


  while (ptrr->next) {
	num_tree_nodes++;
	tree_node *node = (tree_node *)pop(main_stack);
	if ((node != NULL) && (node->sym).is_terminal == true) {
	  if (node->sym.t == EPSILON) {
		  node->token.name = EPSILON;
		  strncpy(node->token.id.str, "epsilon", MAX_LEN);
		continue;
	  }

		if (node->sym.t != tkn.name && tkn.name != ID )
	  {


		node = (tree_node *)pop(main_stack);

		continue;
	  }
		else{

		node->token.line_no = tkn.line_no;
		node->token.name = tkn.name;
		switch (tkn.name) {
		case NUM:
		  node->token.id = tkn.id;
		  break;

		default:
		  strncpy(node->token.id.str, tkn.id.str, MAX_LEN);
		}
		}
	ptrr=ptrr->next;
   	tkn = ptrr->ele;
	  continue;
	}

	if (node == NULL) {

		printf("\nSyntactically correct.\n\n");
	  break;
	}

	int rule_no = parse_table[node->sym.nt][tkn.name];
	if (rule_no == NO_MATCHING_RULE) {

	  while (set_find_elem(follow_set[node->sym.nt], tkn.name) == false) {
		ptrr=ptrr->next;
   		tkn = ptrr->ele;
	  }
	  printf("Token \"%s\" found at line number %d\n",terminal_string[tkn.name], tkn.line_no);
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
  } 

  printf("HELLO KIDDA!");
  return root;

}

void pretty_print(char *s) {
	int column_size = COLUMN_SIZE, len, left_margin;

	len = strlen(s);
	left_margin = (column_size - len) / 2;

	for (int i = 0; i < left_margin; i++)
	{
		printf(" ");
	}

	printf("%s", s);

	int right_margin = left_margin;

	if (len % 2 == 1)
		right_margin++;
	for (int i = 0; i < right_margin; i++)
	{
		printf(" ");
	}

	printf("|");
}


void print_node(tree_node *node)
{
	char *s = (char *)calloc(MAX_LEN, sizeof(char));
	for (int i = 0; i < MAX_LEN; i++)
	{
		s[i] = '\0';
	}

	if(node == NULL)
		return;

	bool is_terminal = (node->sym).is_terminal;

	if (is_terminal == true){

		if((node->token.name != NUM ) && node->token.id.str != NULL)
		{
			snprintf(s, MAX_LEN, "%s", (node->token).id.str);
			pretty_print(s);
		}
		else
		{
			pretty_print("----");
		}
		snprintf(s, MAX_LEN, "%d", (node->token).line_no);
		pretty_print(s);

		if(node->token.id.str != NULL)
		{
			snprintf(s, MAX_LEN, "%s", terminal_string[(node->token).name]);
			pretty_print(s);
		}
		else
		{
			pretty_print("----");
		}

		switch ((node->token).name)
		{
			case NUM:
			{
				snprintf(s, MAX_LEN, "%d", (node->token).id);
				pretty_print(s);
			}
			break;

			default:
			{
				pretty_print("----");
			}
			break;
		}

		snprintf(s, MAX_LEN, "%s", non_terminal_string[(node->parent->sym).nt]);

		pretty_print(s);
		pretty_print("yes");

		printf("\t\t%s\n", terminal_string[(node->sym).t]);
	}
	else
	{
		pretty_print("----");
		pretty_print("----");
		pretty_print("----");
		pretty_print("----");

		if (node->parent)
			pretty_print(non_terminal_string[(node->parent->sym).nt]);
		else
			pretty_print("(ROOT)");

		pretty_print("no");

		printf("\t\t%s\n",non_terminal_string[(node->sym).nt]);
	}
}



void printParseTree(tree_node *root) {
	if (root == NULL)
		return;

	if (root->leftmost_child)
		print_parse_tree(root->leftmost_child);

	print_node(root);

	if (root->leftmost_child)
  	{
		tree_node *temp = root->leftmost_child->sibling;

		while (temp != NULL)
		{
			printParseTree(temp);
			temp = temp->sibling;
		}
  	}
}


void traverseParseTree(tree_node *root){
		if (root == NULL)
		return;

	if (root->leftmost_child)
		print_parse_tree(root->leftmost_child);

	printf("Preorder Traversal of Tree\n");
	print_node(root);

	if (root->leftmost_child)
  	{
		tree_node *temp = root->leftmost_child->sibling;

		while (temp != NULL)
		{
			printParseTree(temp);
			temp = temp->sibling;
		}
  	}
}


void populate_follow_sets() {
  bool is_changed = true;
  int lhs;
  int rhs_sym;
  rhsnode_ptr rhs_ptr;

  set_add_elem(follow_set[MAINPROGRAM], DOLLAR);

  while (is_changed == true)
  {
	is_changed = false;
	for (int i = 0; i < NUM_OF_RULES; i++) {
	  lhs = grammar[i].lhs;
	  rhs_ptr = grammar[i].head;
	  rhsnode_ptr temp = rhs_ptr;
	  while (temp != NULL)
	  {
		if ((temp->sym).is_terminal == false) {
		  rhs_sym = ((temp->sym).nt);
		  set rhs_rule_set = get_rule_first_set(temp->next);
		  set tmp_follow = (ull *)malloc(sizeof(ull) * SET_SIZE);

		  if (tmp_follow == NULL) {
			perror("Follow set memory allocation failed\n");
			exit(1);
		  }

		  for (int j = 0; j < SET_SIZE; j++) {
			tmp_follow[j] = follow_set[rhs_sym][j];
		  }

		  bool eps_in_rhs = false;

		  if (set_find_elem(rhs_rule_set, EPSILON) ==
			  true) 
		  {
			eps_in_rhs = true;
		  }

		  set_remove_elem(rhs_rule_set, EPSILON);

		  set_union(follow_set[rhs_sym], follow_set[rhs_sym], rhs_rule_set);

		  if ((eps_in_rhs == true) || (temp->next == NULL)) {
			set_union(follow_set[rhs_sym], follow_set[rhs_sym],
					  follow_set[lhs]);
		  }

		  for (int j = 0; j < SET_SIZE; j++) {
			if (follow_set[rhs_sym][j] != tmp_follow[j]) {
			  is_changed = true;
			}
		  }
		  free(tmp_follow);
		}
		temp = temp->next;
	  } 
	}   
  }     
}

void populate_first_sets() {
  bool is_changed = true;
  int lhs;
  rhsnode_ptr rhs_ptr;
  while (is_changed == true) 
  {
	is_changed = false;
	for (int i = 0; i < NUM_OF_RULES; i++) {
	  lhs = grammar[i].lhs;
	  rhs_ptr = grammar[i].head;
	  if ((rhs_ptr->sym).is_terminal ==true) 
	  {
		token_name t = (rhs_ptr->sym).t;
		if (set_find_elem(first_set[lhs], t) ==false) 
		{
		  set_add_elem(first_set[lhs], t);
		  is_changed = true;
		}
	  } else // nonterminal
	  {
		rhsnode_ptr temp = rhs_ptr;
		ull *rhs_symbol_fset;
		ull *lhs_symbol_fset = first_set[lhs];
		while (temp != NULL) 
		{
		  if ((temp->sym).is_terminal ==
			  true) 
		  {
			token_name t = (temp->sym).t;
			if (set_find_elem(first_set[lhs], t) ==false) 
					   
			{
			  set_add_elem(first_set[lhs], t);
			  is_changed = true;
			}
			break;
		  }

		  rhs_symbol_fset = first_set[(temp->sym).nt];

		  bool is_diff = false;
		  bool eps_in_rhs = false;
		  bool eps_in_lhs = false;

		  if (set_find_elem(rhs_symbol_fset,
							EPSILON) ==
			  true) 
		  {
			eps_in_rhs = true;
			set_remove_elem(rhs_symbol_fset, EPSILON);
		  }

		  if (set_find_elem(lhs_symbol_fset, EPSILON) == true) {
			eps_in_lhs = true;
		  }

		  if (is_superset(lhs_symbol_fset, rhs_symbol_fset) ==false) 
					 // have in it's fset
		  {
			is_changed = true;
			set_union(lhs_symbol_fset, lhs_symbol_fset, rhs_symbol_fset);

			if (eps_in_rhs ==
				false) 
			{
			  break;
			} else {
			  set_add_elem(rhs_symbol_fset, EPSILON); 
			  if (eps_in_lhs == false) {
				if (temp->next == NULL) 
						
				{
				  set_add_elem(lhs_symbol_fset, EPSILON);
				  is_changed = true;
				}
			  }
			}
		  } else 
		  {
			if (eps_in_rhs == true) {
			  set_add_elem(rhs_symbol_fset, EPSILON); 
			  if (eps_in_lhs == false) {
				if (temp->next == NULL) 
										
				{
				  set_add_elem(lhs_symbol_fset, EPSILON);
				  is_changed = true;
				}
			  }
			}
			break; //
		  }
		  temp = temp->next;
		} 
	  }  
	}     
  }       
} 


set get_rule_first_set(rhsnode_ptr node) {

  set fset = (set)malloc(sizeof(ull) * SET_SIZE);

  if (fset == NULL) {
	perror("get rule first set failed\n");
	exit(1);
  }

  set_init(fset);
  rhsnode_ptr temp = node;
  int sym;

  while (temp != NULL) {
	if ((temp->sym).is_terminal == true) {
	  sym = (temp->sym).t;
	  set_add_elem(fset, sym);
	  return fset;
	}

	else {
	  sym = (temp->sym).nt;
	  set_union(fset, fset, first_set[sym]);

	  if (set_find_elem(first_set[sym], EPSILON) == false) // eps not in the nt
	  {
		return fset;
	  } else {
		if (temp->next != NULL) {
		  set_remove_elem(fset, EPSILON);
		}
	  } 
	}   

	temp = temp->next;
  } 
  return fset;
}


void print_parse_table() {
  for (int i = 0; i < NUM_OF_NONTERMINALS; i++) {
	for (int j = 0; j < NUM_OF_TERMINALS; j++) {
	  if (parse_table[i][j] != NO_MATCHING_RULE) {
		printf("parse_table[%s][%s] : ", non_terminal_string[i],terminal_string[j]);
		print_rule(parse_table[i][j]);
	  }
	}
  }
}

