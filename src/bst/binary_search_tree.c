/* A binary search tree is a tree that has a strict relation between parent and children nodes.
 * The key values at all nodes in the left subtree of a node must be less than the key of the node.
 * The key value at all nodes in the right subtree of a node must be greater than the key of the node.
 * Behaviour of duplicate nodes depends on required behaviour
 */

/* For this API, a binary search tree holding integers is implemented using linked lists. But in general, a node can hold any arbitrary 'value'.
 * A BST can also be implemented by using a array, but it isn't always efficent as a BST doesn't have to be a complete binary tree.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Node struct that is used in a tree */
typedef struct Node
{
    struct Node *parent; // NULL for root
    struct Node *left;
    struct Node *right;
    int value;
    int size;   // subtree size
    int height; // subtree height
} Node;

/* Wrapper for BST*/
typedef struct BST
{
    Node *root;
    int size;
} BST;

// Create new node with value k
Node *create_node(int k)
{
    Node *n = malloc(sizeof(Node));
    if (!n)
    {
        return NULL;
    }
    n->value = k;
    n->size = 1;
    n->height = 0;
    n->parent = NULL;
    n->left = NULL;
    n->right = NULL;
    return n;
}

// Instantiate the BST
BST *create_bst()
{
    BST *tree = malloc(sizeof(BST));
    if (!tree)
    {
        return NULL;
    }

    tree->root = NULL;
    tree->size = 0;

    return tree;
}

/* Traversing a BST or in general can be done in three ways
 * Preorder: Root Left Right
 * Postorder: Left Right Root
 * Inorder: Left Root Right
 * All run in O(n) time where n is number of nodes in tree
 */

// Helper function for preordering
void preorder_node(Node *node)
{
    if (!node)
        return;

    printf("%d ", node->value);
    preorder_node(node->left);
    preorder_node(node->right);
}

// Preorder
void preorder(const BST *tree)
{
    if (!tree || !tree->root)
    {
        return;
    }
    preorder_node(tree->root);
}

// Helper function for postordering
void postorder_node(Node *node)
{
    if (!node)
        return;

    postorder_node(node->left);
    postorder_node(node->right);
    printf("%d ", node->value);
}

// Postorder
void postorder(const BST *tree)
{
    if (!tree || !tree->root)
    {
        return;
    }
    postorder_node(tree->root);
}

// Helper function for inordering
void inorder_node(Node *node)
{
    if (!node)
        return;

    inorder_node(node->left);
    printf("<Value:%d><Size:%d>:<Height:%d> ", node->value, node->size, node->height);
    inorder_node(node->right);
}

// Inorder ---> Gives sorted order of nodes
void inorder(const BST *tree)
{
    if (!tree || !tree->root)
    {
        return;
    }
    inorder_node(tree->root);
}

// Returns node with value k if it exists instead of true/false
Node *search_node(Node *root, int k)
{

    Node *curr = root;

    while (curr)
    {
        if (curr->value == k)
        {
            return curr;
        }
        curr = (k > curr->value) ? curr->right : curr->left; // go right if k is greater than current value, else left
    }

    return NULL;
}

/* Attempt to locate a particular key in a BST by viewing it as a decision tree. Return true if it exists in the tree.
 * Average case is O(log n) but if the tree has the worst balancing possible it can be O(n)
 */
bool search(const BST *tree, int k)
{
    if (!tree || !tree->root)
        return false;

    return search_node(tree->root, k) != NULL;
}

/* For each node on path from n to root update that nodes size including root using relation:
 * size(n) = 1 + size(n.left) + size(n.right)
 */
void update_node_sizes(Node *n)
{
    Node *curr = n; // start from n itself
    while (curr)
    {
        curr->size = 1;
        if (curr->left)
        {
            curr->size += curr->left->size;
        }
        if (curr->right)
        {
            curr->size += curr->right->size;
        }
        // go up
        curr = curr->parent;
    }
}

/* Returns size of subtree rooted at n */
int get_node_size(Node *n)
{
    if (!n)
    {
        return 0;
    }
    return n->size;
}

/* For each node on path from n to root update that nodes height including root using relation:
 * height(n) = 1 + max(height(n.left) + height(n.right))
 */
void update_node_heights(Node *n)
{
    Node *curr = n; // start from n itself
    while (curr)
    {
        int leftH = -1;
        int rightH = -1;
        if (curr->left != NULL)
        {
            leftH = curr->left->height;
        }
        if (curr->right != NULL)
        {
            rightH = curr->right->height;
        }
        int maxH = -1;
        if (leftH > rightH)
        {
            maxH = leftH;
        }
        else
        {
            maxH = rightH;
        }
        curr->height = 1 + maxH;
        curr = curr->parent;
    }
}

/* Returns height of node n */
int get_node_height(Node *n)
{
    if (!n)
    {
        return -1;
    }
    return n->height;
}

void update_tree(Node *n)
{
    update_node_heights(n);
    update_node_sizes(n);
}

// Successor of a node is it's right child's left most descendant if it exisits
// Else go up using parent pointers until a node is a left child
Node *successor(Node *root, int k)
{
    Node *x = search_node(root, k);
    if (!x)
        return NULL;

    // right subtree exists
    if (x->right)
    {
        Node *r = x->right;
        while (r->left)
        {
            r = r->left;
        }
        return r;
    }

    // go up
    Node *p = x->parent;
    while (p && x == p->right)
    {
        x = p;
        p = p->parent;
    }

    return p;
}

// Predecessor of a node is it's left child's right most descendant if it exists
// Else go up using parent pointers until a node is a right child
Node *predecessor(Node *root, int k)
{
    Node *x = search_node(root, k);
    if (!x)
        return NULL;

    // left subtree exists
    if (x->left)
    {
        Node *r = x->left;
        while (r->right)
        {
            r = r->right;
        }
        return r;
    }

    // go up
    Node *p = x->parent;
    while (p && x == p->left)
    {
        x = p;
        p = p->parent;
    }

    return p;
}

Node *insert_node(Node *root, int k)
{
    if (!root)
    { // tree empty make root
        Node *r = create_node(k);
        return r;
    }

    Node *parent = NULL;
    Node *curr = root;
    while (curr)
    {
        parent = curr;
        if (curr->value == k)
        {
            return root;
        }
        if (k > curr->value)
        {
            curr = curr->right;
        }
        else
        {
            curr = curr->left;
        }
    }

    Node *n = create_node(k);
    if (k > parent->value)
    { // set right child of parent to be new node
        n->parent = parent;
        parent->right = n;
    }
    else
    { // set left child of parent to be new node
        n->parent = parent;
        parent->left = n;
    }
    update_tree(n); // update tree stats
    return root;
}

/* Insert new node with value k if it doesn't exist
 */
void bst_insert(BST *tree, int k)
{
    if (!tree)
    {
        return;
    }
    tree->root = insert_node(tree->root, k);
    tree->size++;
}

/* For deleting a node n from a BST we have three cases to consider
 * Case 1 : No children is easy to tackle just set parent's right or left link to NULL
 * Case 2: With 1 child 'bypass' node n and set child of n to child of n's parent
 * Case 3: With two children, find predecessor or sucessor, and make n's value of that nodes value and free it taking care of it's children
 * Special Case: If we want to delete root, the same steps apply from above
 */
Node *delete_node(Node *root, int k, bool *flag)
{
    Node *n = search_node(root, k);
    if (!n)
    {
        return root;
    }

    // Special Case: deleting root
    if (root == n)
    {
        // root with no children
        if (!n->left && !n->right)
        {
            free(n);
            *flag = true;
            return NULL;
        }

        // root with one child
        if (n->left && !n->right)
        {
            Node *child = n->left;
            child->parent = NULL;

            free(n);
            *flag = true;

            update_tree(child);

            return child;
        }

        if (n->right && !n->left)
        {
            Node *child = n->right;
            child->parent = NULL;

            free(n);
            *flag = true;

            update_tree(child);

            return child;
        }

        // root with two children
        Node *s = successor(root, k);
        n->value = s->value;

        Node *ps = s->parent;
        Node *child = s->right;

        if (ps->left == s)
            ps->left = child;
        else
            ps->right = child;

        if (child)
            child->parent = ps;

        free(s);
        *flag = true;

        update_tree(ps);

        return root;
    }

    // Case 1: Zero children
    if (!n->left && !n->right)
    {
        Node *parent = n->parent;

        if (parent->left == n)
        {
            parent->left = NULL;
        }
        else
        {
            parent->right = NULL;
        }

        free(n);
        *flag = true;

        update_tree(parent);

        return root;
    }

    // Case 2: One child only (left)
    if (n->left && !n->right)
    {
        Node *parent = n->parent;
        Node *child = n->left;

        if (parent->left == n)
        {
            parent->left = child;
        }
        else
        {
            parent->right = child;
        }

        child->parent = parent;

        free(n);
        *flag = true;

        update_tree(parent);

        return root;
    }

    // Case 2: One child only (right)
    if (n->right && !n->left)
    {
        Node *parent = n->parent;
        Node *child = n->right;

        if (parent->left == n)
        {
            parent->left = child;
        }
        else
        {
            parent->right = child;
        }

        child->parent = parent;

        free(n);
        *flag = true;

        update_tree(parent);

        return root;
    }

    // Case 3: Two children
    Node *s = successor(root, k);

    n->value = s->value;

    Node *ps = s->parent;
    Node *child = s->right;

    if (ps->left == s)
        ps->left = child;
    else
        ps->right = child;

    if (child)
        child->parent = ps;

    free(s);
    *flag = true;

    update_tree(ps);

    return root;
}

void bst_delete(BST *tree, int k)
{
    if (!tree || !tree->root)
    {
        return;
    }
    bool deleted = false;
    tree->root = delete_node(tree->root, k, &deleted);
    if (deleted)
    {
        tree->size--;
    }
}

// helper function to free nodes
void free_nodes(Node *root)
{
    if (!root)
    {
        return;
    }
    free_nodes(root->left);
    free_nodes(root->right);
    free(root);
}

// free BST
void free_bst(BST *tree)
{
    free_nodes(tree->root); // postorder free
    free(tree);
}

// ============================================================= UPDATE ========================================================================== //
/* All these operations are pretty straightfoward (maybe not the deletion process) but they do not take into account the 'degradation' of trees.
   Some patterns of these operations can skew the tree and we can end up with long branches in the tree and in the worst case end up with a linked
   list tree .The whole point of using a tree data structure is to take advantage of its faster operations,and
   we know when a tree in general is 'proper' it is much faster than a linked list.
   We have two choices to tackle this problem.
     a.) Global rebuild of the existing tree 
     b.) Continious rotations after operations
   In this implementation, you can either choose the BALANCING_TYPE as GLOBAL_BALANCE,ROTATION_BALANCE,or NO_BALANCE
   (BST instance doesn't need rebalancing).
   The balancing flags are described in detail below:

   GLOBAL_REBUILD (Scapegoat-style balancing)
        - Periodically reconstructs parts or the entirety of the tree.
        - Uses structural criteria (e.g., subtree size imbalance or log(n) height bounds)
          to determine when a rebuild is necessary.
        - Provides strong amortized guarantees with simpler local operations.
        - Suitable for batch-heavy or analysis-friendly workloads.

    ROTATION_BALANCE (AVL-style balancing)
        - Maintains strict balance constraints using local rotations after insertions and deletions.
        - Ensures height remains O(log n) at all times.
        - Provides consistent worst-case performance per operation.
        - Preferred for real-time or frequently updated datasets.

    NO_BALANCE (Plain BST)
        - No structural adjustments are performed.
        - Tree shape depends entirely on insertion order.
        - Simplest implementation but may degrade to O(n) operations in worst case.
        - Suitable only when input is known to be well-distributed or balancing is handled externally.
*/

// NOT IMPLEMENTED YET SOON ...
