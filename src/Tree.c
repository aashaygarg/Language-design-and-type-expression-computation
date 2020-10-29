#include "Tree.h"
#include<stdbool.h>

tree_node *create_tree_node() {
  tree_node *node = (tree_node *)malloc(sizeof(tree_node));
  if (node == NULL) {
    perror("tree_node allocation error..\n");
    exit(0);
  }
  node->parent = NULL;
  node->sibling = NULL;
  node->leftmost_child = NULL;
  node->rightmost_child = NULL;
  node->num_child = 0;
  return node;
}

void add_child(tree_node *parent, tree_node *child) {
  if (parent->rightmost_child == NULL) {
    parent->leftmost_child = child;
    parent->rightmost_child = child;
  } else {
    parent->rightmost_child->sibling = child;
    parent->rightmost_child = child;
  }
  parent->num_child++;
  child->parent = parent;
  child->sibling = NULL;
}

tree_node *get_nth_child(tree_node *root, int n){
	if((root == NULL) || (n > root->num_child))
		return NULL;
	
	tree_node *tmp_child = root->leftmost_child;

	for(int i = 1; i < n; i++){		// loop tells how many child u have to go ahead
		tmp_child = tmp_child->sibling;
	}

	return tmp_child;
}
