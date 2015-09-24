/*
 * rb_tree.c
 *
 *  Created on: Sep 19, 2015
 *      Author: Sergey
 */

#include "rb_tree.h"
#ifdef _MSC_VER
#define inline __inline
#endif

 /*some definitions here to make it look like Cormen's style*/
#define p(x) (x)->parent 
#define left(x) (x)->left
#define right(x) (x)->right
#define color(x) (x)->color
#define key(x) (x)->key

 /*"private" functions for tree rotations*/
static inline void left_rotate(rb_tree_t *tree, rb_node_t * x) {
	rb_node_t *parent = p(x);
	rb_node_t *y = right(x);
	rb_node_t *y_left = left(x);
	/*reassignments*/
	right(x) = y_left;
	p(y_left) = x;
	p(y) = parent;
	p(x) = y;
	left(y) = x;
	if (parent == NULL) {
		tree->root = y;
	}
	else {
		if (left(parent) == x) {
			left(parent) = y;
		}
		else {
			right(parent) = y;
		}
	}
};
static inline void right_rotate(rb_tree_t *tree, rb_node_t* y) {
	rb_node_t *parent = p(y);
	rb_node_t *x = left(y);
	rb_node_t *x_right = right(x);
	/*reassignment*/
	right(x) = y;
	p(y) = x;
	left(y) = x_right;
	p(x_right) = y;
	p(x) = parent;
	if (parent == NULL) {
		tree->root = x;
	}
	else {
		if (left(parent) == y) {
			left(parent) = x;
		}
		else {
			right(parent) = x;
		}
	}
};

/*"private" fix-up functions*/
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
	while (x != tree->root && color(x) == BLACK) {
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

/*node allocation and init*/
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

/*tree alloc and init*/
rb_tree_t *rb_tree_create(rb_tree_compare *comp) {
	rb_tree_t *tree = (rb_tree_t*)malloc(sizeof(rb_tree_t));
	tree->cmpr = comp;
	//rb_node_t *root = NULL /*node_create(NULL, NULL, BLACK)*/;
	tree->root = NULL;
	/*tree->height = 0;*/
	return tree;
}

int rb_tree_insert(rb_node_t *node, rb_tree_t *tree) {
	rb_tree_compare *cmpr = tree->cmpr; /*key comparator function*/
	rb_node_t *currnode = tree->root;
	rb_node_t *ref_node = NULL; /*stores a leaf node to which we will append new node*/
	while (currnode != NULL) {
		ref_node = currnode;
		if (cmpr(key(currnode), key(node)) == 1) {
			currnode = left(currnode);
		}
		else {
			currnode = right(currnode);
		}
	};
	p(node) = ref_node;
	if (ref_node == NULL) { /*no nodes in the tree*/
		tree->root = node;
	}
	else {
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
	rb_tree_compare *cmpr = tree->cmpr; /*key comparator function*/
	rb_node_t *currnode = tree->root;
	rb_node_t *ref_node = NULL; /*stores a node*/
	while (currnode != NULL) {
		ref_node = currnode;
		if (cmpr(key(currnode), key) == 0) break;
		if (cmpr(key(currnode), key) == 1) {
			currnode = left(currnode);
		}
		else {
			currnode = right(currnode);
		}
	};
	return ref_node;
}