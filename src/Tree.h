#ifndef TR_H
#define TR_H

#include<stdbool.h>
#include "grammar_read.h"

typedef struct TREENODE
{
	struct TREENODE *parent;
	struct TREENODE *sibling;
    struct TREENODE *leftmost_child;
    struct TREENODE *rightmost_child;

    symbol sym;
    ELEMENT token;
    int num_child;
} tree_node;

tree_node *create_tree_node();
void add_child(tree_node *parent, tree_node *child);
tree_node *get_nth_child(tree_node *root, int n);

#endif