#include "rb_tree.h"
#include <stdio.h>
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
	rb_tree_insert(tree, node_create(NULL, (void*)1));
	rb_tree_insert(tree, node_create(NULL, (void*)2));
	rb_tree_insert(tree, node_create(NULL, (void*)3));
	return 0;
}