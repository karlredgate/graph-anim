
#include <stdlib.h>

typedef struct binary_tree binary_tree;

typedef int (*binary_tree_comparator)( void *, void * );

struct binary_tree {
    void *data;
    binary_tree_comparator compare;
    binary_tree *left;
    binary_tree *right;
};

binary_tree *
binary_tree_create( void *key ) {
    binary_tree *node = malloc( sizeof (binary_tree) );
    node->left = NULL;
    node->right = NULL;
    node->data = key;
    return node;
}

binary_tree *
binary_tree_find( binary_tree *node, void *key ) {
    if ( node == NULL ) return NULL;
    int result = node->compare( key, node->data );
    if ( result < 0 ) return binary_tree_find( node->left, key );
    if ( result > 0 ) return binary_tree_find( node->right, key );
    return node;
}

binary_tree *
binary_tree_insert( binary_tree *node, void *key ) {
    if ( node == NULL ) return binary_tree_create( key );
    int result = node->compare( key, node->data );
    if ( result < 0 ) {
        node->left = binary_tree_insert( node->left, key );
    }
    if ( result > 0 ) {
        node->right = binary_tree_insert( node->right, key );
    }
    return node;
}

/*
 * Pass in a pointer to the section of the tree so that that
 * part of the tree can be written.
 * Search down the left of the tree until there is no left child.
 * This is the minimum node.  
 */
void *
binary_tree_delete_min( binary_tree **tree ) {
    binary_tree *node = *tree;
    if ( node->left != NULL ) return binary_tree_delete_min( &(node->left) );
    void *data = node->data;
    *tree = node->right;
    free( node );
    return data;
}

void
binary_tree_delete( binary_tree **tree, void *key ) {
}

/* vim: set autoindent expandtab sw=4 : */
