/*
 * rb_tree.c
 *
 *  Created on: Sep 19, 2015
 *      Author: sergey
 */

#include "rb_tree.h"
#ifdef _MSC_VER
#define inline __inline
#endif

#define p(x) (x)->parent /*quick define for node's parent*/
#define left(x) (x)->left
#define right(x) (x)->right
#define color(x) (x)->color
#define key(x) (x)->key
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
	}
	else {
		if (parent->left == x) {
			parent->left = y;
		}
		else {
			parent->right = y;
		}
	}
};
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
	}
	else {
		if (parent->left == y) {
			parent->left = x;
		}
		else {
			parent->right = x;
		}
	}
};
/*fix-up functions*/
static int rb_tree_insert_fixup(rb_tree_t *tree, rb_node_t *x) {
	while (p(x)->color & RED) { /*move up the tree*/
		if (p(x) == left(p(p(x)))) { /*DO THE LEFT PART*/
			rb_node_t *uncle = right(p(p(x)));
			/*CASE 1, UNCLE AND PARENT NODES ARE BOTH RED*/
			if (uncle->color & RED) {
				uncle->color = p(x)->color = BLACK; /*recolor*/
				p(p(x))->color = RED;
				x = p(p(x)); /*move pointer up, x is now grandparent node*/
			}
			/*CASE 2 &3, X'S UNCLE IS BLACK */
			else {
				/*CASE 2, X IS A RIGHT CHILD OF ITS PARENT*/
				if (x == right(p(x))) {
					x = p(x);
					left_rotate(tree, x);
				};
				/*CASE 3, X IS A LEFT CHILD OF ITS PARENT*/
				if (x == right(p(x))) { /*check just in case*/
					p(x)->color = BLACK;
					p(p(x))->color = RED;
					right_rotate(tree, p(p(x)));
				};
			}
		}
		else { 
			/*IF THE NODE IS ON THE LEFT SIDE, SYMMETRICAL TO THE CODE ABOVE*/
			rb_node_t *uncle = left(p(p(x)));
			/*CASE 1, UNCLE AND PARENT NODES ARE BOTH RED*/
			if (uncle->color & RED) {
				uncle->color = p(x)->color = BLACK; /*recolor*/
				p(p(x))->color = RED;
				x = p(p(x)); /*move pointer up, x is now grandparent node*/
			}
			/*CASE 2 &3, X'S UNCLE IS BLACK */
			else {
				/*CASE 2, X IS A LEFT CHILD OF ITS PARENT*/
				if (x == left(p(x))) {
					x = p(x);
					right_rotate(tree, x);
				};
				/*CASE 3, X IS A RIGHT CHILD OF ITS PARENT*/
				if (x == left(p(x))) { /*check just in case*/
					p(x)->color = BLACK;
					p(p(x))->color = RED;
					left_rotate(tree, p(p(x)));
				};
			}
		}
	}
	tree->root->color = BLACK; /*restore root's color*/
	return 0;
}

static int rb_tree_delete_fixup(rb_tree_t *tree, rb_node_t *x) {
	/*TODO*/
	while (x != tree->root && color(x) == BLACK ) {
		/*if x is a left child of its parent*/
		if (x == left(p(x))) {
			/*get x's sibling, w*/
			rb_node_t *w = right(p(x));
			/*CASE 1, w is RED*/
			if (color(w) == RED) {
				/*recolor w BLACK, recolor parent RED*/
				color(w) = BLACK;
				color(p(x)) = RED;
				left_rotate(tree, p(x));
				w = right(p(x));
			}
			/*CASE 2*/
			if (color(left(w)) == BLACK && color(right(w)) == BLACK) {
				color(w) = RED;
				x = p(x);
			}
			/*CASE 3 & 4*/
			else {
				/*CASE 3*/
				if (color(right(w)) == BLACK) {
					color(left(w)) = BLACK;
					color(w) = RED;
					right_rotate(tree, w);
					w = right(p(x));
				};
				color(w) = color(p(x));
				color(p(x)) = BLACK;
				color(right(w)) = BLACK;
				left_rotate(tree, p(x));
				x = tree->root;
			}
		} /*if x is a right child of its parent, mirrors code above*/
		else {
			/*get x's sibling, w*/
			rb_node_t *w = left(p(x));
			/*CASE 1, w is RED*/
			if (color(w) == RED) {
				/*recolor w BLACK, recolor parent RED*/
				color(w) = BLACK;
				color(p(x)) = RED;
				right_rotate(tree, p(x));
				w = left(p(x));
			}
			/*CASE 2*/
			if (color(left(w)) == BLACK && color(right(w)) == BLACK) {
				color(w) = RED;
				x = p(x);
			}
			/*CASE 3 & 4*/
			else {
				/*CASE 3*/
				if (color(left(w)) == BLACK) {
					color(right(w)) = BLACK;
					color(w) = RED;
					left_rotate(tree, w);
					w = left(p(x));
				};
				color(w) = color(p(x));
				color(p(x)) = BLACK;
				color(left(w)) = BLACK;
				right_rotate(tree, p(x));
				x = tree->root;
			}
		}
	}
	return 0;
}

rb_node_t *node_create(void *p, void *key, int color) {
	rb_node_t *node = (rb_node_t*)malloc(sizeof(rb_node_t));
	node->p = p;
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	node->color = color;
	return node;
}

rb_tree_t *rb_tree_create(rb_tree_compare *comp) {
	rb_tree_t *tree = (rb_tree_t*)malloc(sizeof(rb_tree_t));
	tree->cmpr = comp;
	rb_node_t *root = node_create(NULL, NULL, BLACK);
	tree->root = root;
	tree->height = 0;
	return tree;
}

int rb_tree_insert(rb_node_t *node, rb_tree_t *tree) {
	/*TODO*/
	rb_tree_compare *cmpr = tree->cmpr; /*key comparator function*/
	rb_node_t *currnode = tree->root;
	rb_node_t *ref_node = NULL; /*stores a leaf node to which we will append new node*/
	while (currnode != NULL) {
		if ( cmpr(key(currnode), key(node)) == 1 ) {
			currnode = left(currnode);
		}
		else {
			currnode = right(currnode);
		}
	};
	p(node) = ref_node;
	if (ref_node == NULL) { /*no nodes in the tree*/
		tree->root = node;
	}	else {
		/*found the node, deciding whether to append to the left or to the right*/
		if (cmpr(key(ref_node), key(node)) == 1) {
			left(ref_node) = node;
		}
		else {
			right(ref_node) = node;
		}
	};
	left(node) = right(node) = NULL;
	color(node) = RED;
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
