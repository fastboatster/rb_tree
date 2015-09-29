#include "rb_tree.h"
#include <stdio.h>
#include <stdlib.h>
#define NUM_NODES 6
int comp(void *key1, void *key2) {
	int k1 = (int)key1;
	int k2 = (int)key2;
	if (k1 == k2) return 0;
	if (k1 > k2) return 1;
	return -1;
}
int main(int argc, char** argv) {
	printf( "%s", "Starting the test:\n");
	
	rb_tree_t *tree = rb_tree_create(&comp);
	//testing insertion to the right part of the tree
	rb_tree_insert(tree, node_create(NULL, (void*)6));
	rb_tree_insert(tree, node_create(NULL, (void*)6));
	rb_tree_insert(tree, node_create(NULL, (void*)7));
	rb_tree_insert(tree, node_create(NULL, (void*)8));
	rb_tree_insert(tree, node_create(NULL, (void*)9));
	rb_tree_insert(tree, node_create(NULL, (void*)9));
	
	//testing insertion to the left
	rb_tree_insert(tree, node_create(NULL, (void*)6));
	rb_tree_insert(tree, node_create(NULL, (void*)5));
	rb_tree_insert(tree, node_create(NULL, (void*)4));
	rb_tree_insert(tree, node_create(NULL, (void*)4));
	rb_tree_insert(tree, node_create(NULL, (void*)3));
	rb_tree_insert(tree, node_create(NULL, (void*)2));
	rb_tree_insert(tree, node_create(NULL, (void*)1));
	rb_tree_insert(tree, node_create(NULL, (void*)1));
	rb_tree_insert(tree, node_create(NULL, (void*)0));
	rb_tree_t *rand_tree = rb_tree_create(&comp);
	/*testing random number insertion*/
	time_t t;
	/* Intializes random number generator */
	srand((unsigned)time(&t));
	int i, val;
	for (i = 0; i < NUM_NODES; i++) {
		val = rand() % 50;
		printf("Inserting %d\n", val);
		rb_tree_insert(rand_tree, node_create(NULL, (void*)val));
	};
	return 0;
}