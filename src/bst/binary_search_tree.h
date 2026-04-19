#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdbool.h>

typedef struct Node Node;
/* Wrapper for BST*/
typedef struct BST
{
    Node *root;
    int size;
} BST;

BST *create_bst();
void preorder(const BST *tree);
void postorder(const BST *tree);
void inorder(const BST *tree);
bool search(const BST *tree, int k);
void bst_insert(BST *tree, int k);
void bst_delete(BST *tree, int k);
void free_bst(BST *root);

#endif