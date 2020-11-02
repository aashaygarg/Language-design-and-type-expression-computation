# Language-design-and-type-expression-computation

Functions prototypes

 readGrammar( “grammar.txt”, grammar G): 
This function reads the grammar rules line by line from the file grammar.txt and populates the array of linked list G. Each cell of the array holds the LHS nonterminal of the production rule, and the linked list contains the remaining symbols of terminals and nonterminals.

 tokeniseSourcecode( “sourcecode.txt”, tokenStream *s): 
The source code text is read from the file “sourcecode.txt” and processed for extracting the names and symbols, all separated by blank spaces. It captures the line numbers, lexemes and the appropriate token names to populate the nodes of the linked list s.

 createParseTree( parseTree *t, tokenStream *s, grammar G): 
This function uses the start symbol for deriving the complete program, and looks at the tokens in the tokenStream sequentially. Based on the next token, it selects the rule to expand the nonterminals maintained in the stack. The function of stack is same that of push down automata. The stack symbols are the symbols of right hand sides of the grammar rules, which can be both terminals and non-terminals. The derivation to be implemented is left to right derivation, which expands the nonterminal at the left first and maintains remaining nonterminals in the stack. The flow of terminals and nonterminals is last in first out, therefore, the right hand side symbols of the selected grammar rule are pushed onto the stack in such a way that the first symbol on the RHS of the rule goes to the top of the stack to ensure left most derivation. The right hand side of a rule has number of terminals and nonterminals, therefore the stack node should be capable of storing the information whether the symbol stored is a nonterminal or a terminal. This will help in matching the top of the stack with the next token. If the top of the stack is a non-terminal, then it is expanded further without consuming the input token. If the top of the stack is a terminal, then, it is checked whether it matches the next token (called lookahead). If the top of the stack terminal symbol is epsilon, then the rule is selected appropriately. The epsilon is popped out in such a way that the next symbol on the stack, if a terminal matches with the input token, or if a non-terminal is expanded. Each nonterminal A, if expanded using rule A α, where α is the stream of terminals and nonterminals on the RHS of the rule, then becomes the parent node for all its children in α. For all test cases, it is assumed that the code is syntactically correct; this means there is no grammatical mistake in the code. Therefore, there is no possibility of encountering any error while creating the parse tree. Of course, when the next token does not match with the top of the stack terminal symbol, then you should modify your technique for rule selection and select the rule appropriately. At the end, print a message that “parse tree is created successfully”.

 traverseParseTree(parseTree *t, typeExpressionTable T ): The parse tree is traversed from its root ‘t’, and its children are traversed from left to right. The sub-trees corresponding to the non-leaf nodes labelled as declaration statements are traversed for type expression computation via one branch of it. In this process, the information will propagate from children nodes to parent nodes. The other branch comprising the list of variables is traversed to pick up the variable names (tokenized as ID) and the computed type is associated appropriately. In this process, the type information residing at the root of the subtree, is propagated down to the leaf nodes. Each variable at the leaf node in this subtree in the corresponding declaration thus gets a type. Before entering into the subtree corresponding to next statement, the function also populates the typeExpressionTable for each variable name found in the list of variables along with its associated type. The typeExpressionTable is fully populated before it enters the other branch comprising all assignment statements. It is assumed that the variables used in any expressions should have been declared in the program. This is to minimize your work on checking whether a variable is declared or not, which will fall in the scope of compiler construction course later. Hence all test cases created by you, must have all the variables used in the expressions declared previously.
If the sub-tree corresponding to the assignment statement is traversed, then the types of the variable identifier at the left hand side of the assignment statement, and the types of variables used in the expression are obtained from the typeExpressionTable. For each occurrence of any variable, the typeExpressionTable is searched to obtain type of the variable; therefore, the typeExpressionTable should be implemented efficiently. Consider an expression a+b-c*d, then if the types of the operands of the sub-expression (say c*d) follow the permissible rules for types defined above for the used operator, then the type of the non terminal in the parse tree corresponding to the expression c*d is populated in the root of the corresponding sub-tree. Next the type of the variable identifier b is obtained from the typeExpressionTable, and the type expression stored in the root for c*d is used for type checking the feasibility of – (minus operation) in the sub-expression b-c*d. If this follows the type rules, then the type of this sub-expression is stored in the root node (the non-leaf node) corresponding to the sub-tree for this sub-expression. This continues until the traversal reaches back to the non-leaf node corresponding to the RHS expression of the assignment statement. If the type of the expression and the type of left hand side variable identifier follow the type rules for assignment operator, then the next assignment statement is picked for traversal, else a type error is indicated with line number (of source code).
An array element used in the expression such as u [ 2 5 ] will be required to be verified for its type from the table entry for u. If the index while accessing an element is not a variable identifier (as in u [ k m ] ), the type of u is not a dynamic array, if the range values preserved in the type expression for u allow usage of indices 2 and 5 in the respective dimensions, and are with in permissible ranges (bound), then the element access is type error free, else an error will be reported.

All type errors are printed in the following details in the same order in each line on the console
 Line number ( This refers to the line number in the leaf node taken from the token stream at the time of creating parse tree. The errors printed without this line number will not get any credit.)
 Statement type (declaration or assignment)
 operator
 lexeme of first operand
 type of first operand
 lexeme of second operand
 type of second operand
 position in the parse tree in terms of its depth from parse tree’s root node (take root node depth as 0)
 short message (in maximum 30 characters length)
The statement type is either declaration statement or an assignment statement. If the error was in size mismatch of three dimensional jagged arrays, then print a message “3D JA size mismatch” while marking *** for operator and other fields which are not applicable in declaration statement. If the error was in any assignment statement then report that appropriately. Make sure that your error messages are column justified (you can use %12d, %20s etc. in your printf statement to justify the details). All details above, corresponding to an error must be printed in single line on the console. The type expressions, even if enumerated at the internal level, should be printed in user readable form as has been mentioned above.

 printParseTree(parseTree *t): prints the parse tree nodes in the preorder traversal in the following format
 Symbol name
 Whether terminal or non terminal
 Type expression stored in the corresponding node (if non-leaf)
 Name of lexeme (if leaf node)
 Line number (if leaf node)
 Grammar rule applied for expansion of this node while parsing (if non leaf)
 Depth of node (root of the parse tree at depth 0)
All of these for one will have to be justified in pretty columns and will be printed only in a line. Similarly keep printing the nodes information line after line.

 printTypeExpressionTable (typeExpressionTable T): This function prints all four field details stored in the type expression table as described above. The printing format is as follows
Field 1 Field 2 Field 3 Field 4
Print the details line by line for each variable. All field details should be justified to give clear view of details. The type expression should also be printed in human readable form irrespective of how you enumerated the types.

 Driver function: You should create the driver (main) function that uses options in loops and continues being in loop until receives a 0 as an option.
Option 0: exit
Option 1: Create parse tree
Option 2: Traverse the parse tree to construct typeExpressionTable. Also print the type errors while traversing the parse tree and accessing the typeExpressionTable.
Option 3: Print parse tree in the specified format
Option 4: Print typeExpressionTable in the specified format.
Also, ensure that all options are independent of each other. For example, option 2 must first create the parse tree and then traverse appropriately. Similarly the Option 1 created earlier should be independent from other options.

Implementation platform and compiler: 
All implementation will be required to be done in C programming language. You should use the Ubuntu (version 20.04.1 LTS) and GCC (version 9.3.0) strictly for all your implementations. If you have only windows operating system, then install Ubuntu on the virtual box (free from oracle) and install the given gcc version for compiling this code. 
