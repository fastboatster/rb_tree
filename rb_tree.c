/*
 * rb_tree.c
 *
 *  Created on: Sep 19, 2015
 *      Author: sergey
 */

#include "rb_tree.h"

/*"private" function for tree rotations*/
static inline void left_rotate(rb_tree_t *tree, rb_node_t * x) {
	rb_node_t *parent = x->parent;
	rb_node_t *y = x->right;
	rb_node_t *y_left = y->left;
	/*reassignments*/
	x->right = y_left;
	y_left->parent = x;
	y->parent = parent;
	x->parent = y;
	y->left = x;
	if (parent == NULL) {
		tree->root = y;
	} else {
		if (parent->left == x) {
			parent->left = y;
		} else {
			parent->right = y;
		}
	}
}
static inline void right_rotate(rb_tree_t *tree, rb_node_t* y) {
	rb_node_t *parent = y->parent;
	rb_node_t *x = y->left;
	rb_node_t *x_right = x->right;
	/*reassignment*/
	x->right = y;
	y->parent = x;
	y->left = x_right;
	x_right->parent = y;
	x->parent = parent;
	if (parent == NULL) {
		tree->root = x;
	} else {
		if (parent->left == y) {
			parent->left = x;
		} else {
			parent->right = x;
		}
	}
}
/*fix-up functions*/
static int rb_tree_insert_fixup(rb_tree_t *tree, rb_node_t *x) {
	/*TODO*/
	return 0;
}

static int rb_tree_delete_fixup(rb_tree_t *tree, rb_node_t *x) {
	/*TODO*/
	return 0;
}

rb_node_t *node_create(void *p, void *key, int color) {
	rb_node_t *node = (rb_node_t*) malloc(sizeof(rb_node_t));
	node->p = p;
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	node->color = color;
	return node;
}

rb_tree_t *rb_tree_create(rb_tree_compare comp) {
	rb_tree_t *tree = (rb_tree_t*) malloc(sizeof(rb_tree_t));
	tree->cmpr = comp;
	rb_node_t *root = node_create(NULL, NULL, BLACK);
	tree->root = root;
	tree->height = 0;
	return tree;
}

int rb_tree_insert(rb_node_t *node, rb_tree_t *tree) {
	/*TODO*/
	rb_tree_insert_fixup(tree, node);
	return 0;
}

int rb_tree_delete(rb_node_t *node, rb_tree_t *tree) {
	/*TODO*/
	rb_tree_delete_fixup(tree, node);
	return 0;
}

rb_node_t *rb_tree_lookup(void *key, rb_tree_t *tree) {

	rb_node_t *root = tree->root;
	/*TODO*/
	return NULL;
}
