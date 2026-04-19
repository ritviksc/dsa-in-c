#include <stdio.h>
#include <stdlib.h>
#include "binary_search_tree.h"

int main(void)
{
    BST *root = create_bst();
    if (root)
    {
        printf("Incorrect creation!");
        free_bst(root);
    }

    // set root
    bst_insert(root, 10);
    bst_insert(root, 10);
    inorder(root);
    free_bst(root);
    return EXIT_SUCCESS;
}