#include "grammar_read.h"
#include "driver.h"

void populate_terminal_string() {

	FILE *file = fopen("tokens.txt", "r");
	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *t_file = malloc(sizeof(char) * (length + 1));
	if (t_file == NULL) {
		perror("terminal_string filling failed\n");
		exit(1);
	}

	fread(t_file, sizeof(char), length, file);
	t_file[length] = '\0';
	fclose(file);

	char *tk_read = NULL;
	int i;
	tk_read = strtok(t_file, ", \n");

	for (i = 0; tk_read != NULL; i++) {
		strncpy(terminal_string[i], tk_read, MAX_SYMBOL_LENGTH);
		tk_read = strtok(NULL, ", \n");
	}

	free(t_file);
}

void populate_non_terminal_string() {
	FILE *file = fopen("non_terminal.txt", "r");

	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *nt_file = malloc(sizeof(char) * (length + 1));

	fread(nt_file, sizeof(char), length, file);
	nt_file[length] = '\0';
	fclose(file);

	char *nt_read = NULL;
	int i;
	nt_read = strtok(nt_file, ", \n");

	for (i = 0; nt_read != NULL; i++) {
		strncpy(non_terminal_string[i], nt_read, MAX_SYMBOL_LENGTH);
		nt_read = strtok(NULL, ", \n");
	}
	free(nt_file);
}

void parser_init() {

  init_hash_table(terminal_table);
  init_hash_table(non_terminal_table);

  // initialize all first sets to be null
  for (int i = 0; i < NUM_OF_NONTERMINALS; i++) {
	set_init(first_set[i]);
  }

  for (int i = 0; i < NUM_OF_TERMINALS; i++) {
	hash_insert(terminal_table, terminal_string[i], i);
  }

  for (int i = 0; i < NUM_OF_NONTERMINALS; i++) {
	hash_insert(non_terminal_table, non_terminal_string[i], i);
  }

  for (int i = 0; i < NUM_OF_NONTERMINALS; i++) {
	for (int j = 0; j < NUM_OF_TERMINALS; j++) {
	  parse_table[i][j] = NO_MATCHING_RULE;
	}
  }

	num_tree_nodes = 0;
}


/**
 * @brief inserts a symbol at end of the given rule's list
 *
 * @param ptr_tail - tail pointer to rule's linked list
 * @param sym - symbol to be inserted
 */
void insert_at_end(rhsnode_ptr *ptr_tail, symbol sym) {

  rhsnode_ptr node = (rhsnode_ptr)malloc(sizeof(rhsnode));

  if (node == NULL) {
	perror("insertion at end failed\n");
	exit(1);
  }
  node->sym = sym;
  node->next = NULL;

  if (*ptr_tail != NULL) {
	(*ptr_tail)->next = node;
  }
  *ptr_tail = node;
}

symbol get_symbol(char str[]) {
  symbol sym;
  if ((str[0] >= 'A') && (str[0] <= 'Z')) {
	sym.is_terminal = 0;
	sym.nt = search_hash_table(non_terminal_table, str);
  } else {

	sym.is_terminal = 1;
	char tmp[strlen(str)];
	strcpy(tmp, str);
	for (int i = 0; i < strlen(tmp); i++) {
	  tmp[i] = toupper(tmp[i]);
	}
	sym.t = search_hash_table(terminal_table, tmp);
  }
  return sym;
}

void readGrammar() {

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

    int rule_num = 0;
    char buffer[RHS_MAX_LENGTH];

    while (fgets(buffer, sizeof(buffer), fptr) != NULL) {
        char *sym_read;
        int i;

        sym_read = strtok(buffer, " \n");
        for (i = 0; sym_read != NULL; i++) {
            if (i == 0) // LHS of a production
            {
            //printf("%d",get_symbol(sym_read).nt);
            grammar[rule_num].lhs = get_symbol(sym_read).nt;
            grammar[rule_num].head = NULL;
            grammar[rule_num].tail = NULL;
            } else {
            symbol sym = get_symbol(sym_read);
            insert_at_end(&(grammar[rule_num].tail), sym);
            if (grammar[rule_num].head == NULL) {
                grammar[rule_num].head = grammar[rule_num].tail;
            }
            }
            sym_read = strtok(NULL, " \n");
        }
	rule_num++;
  }
}

void print_symbol(symbol sym) {
    if (sym.is_terminal == true) {
        printf("%s", terminal_string[sym.t]);
    } else {
        printf("%s", non_terminal_string[sym.nt]);
    }
}

void print_rule(int rule_no) {
  int lhs = grammar[rule_no].lhs;
  rhsnode_ptr head = grammar[rule_no].head;
  printf("%s -> ", non_terminal_string[lhs]);
  while (head != NULL) {
	print_symbol(head->sym);
	printf(" ");
	head = head->next;
  }
  printf("\n");
}

void print_grammar() {
  for (int i = 0; i < NUM_OF_RULES; i++)
	{print_rule(i);}

}


