/*
 * rb_tree.h
 *
 *  Created on: Sep 19, 2015
 *      Author: sergey
 */

#ifndef RB_TREE_H_
#define RB_TREE_H_

#include <stddef.h>
#include <stdlib.h>

#define RED 0x1
#define BLACK 0x2

struct rb_node;
struct rb_tree;

typedef struct rb_node {
	int color;
	struct rb_node* parent;
	struct rb_node *left;
	struct rb_node *right;
	void *p;
	void *key;
} rb_node_t;

/*comparator function, returns 0 if key1 and key2 are equal, 1 if key1 is bigger than key2, -1 if vice versa*/
typedef int rb_tree_compare(void* key1, void *key2);

typedef struct rb_tree {
	rb_node_t *root;
	/*int height;*/
	rb_tree_compare *cmpr;
} rb_tree_t;

rb_tree_t *rb_tree_create(rb_tree_compare cmpr);

int rb_tree_destroy(rb_tree_t *tree);

rb_node_t *node_create(void *p, void *key, int color);

int rb_tree_insert(rb_node_t *node, rb_tree_t *tree);

int rb_tree_delete(rb_node_t *node, rb_tree_t *tree);

rb_node_t *rb_tree_lookup(void *key, rb_tree_t *tree);

#endif /* RB_TREE_H_ */
