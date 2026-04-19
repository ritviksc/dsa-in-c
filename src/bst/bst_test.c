#include <stdio.h>
#include <stdlib.h>
#include "binary_search_tree.h"

int main(void)
{
    BST *tree = create_bst();
    if (tree->root)
    {
        printf("Incorrect creation!");
        free(tree->root);
        free_bst(tree);
    }

    // set root
    bst_insert(tree, 10);
    bst_insert(tree, 10);
    inorder(tree);
    free_bst(tree);
    return EXIT_SUCCESS;
}