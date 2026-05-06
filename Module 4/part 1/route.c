// This file is about the way of routing (travelling) through the tree, on which has 3 ways:
// pre order, in order and post order, and each of them has it's differences and aplications
// in specific tasks that requires doing something to a binary tree.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The structure of a node on a binary tree:
struct node {
    // Name or value of the node:
    char value[50];

    // Pointer to the left side:
    struct node* left;
    // Pointer to the right side:
    struct node* right;
};

// Pre order, visits the main node first (root), then the left side, and lastly the right side.
// Travels through the tree in pre order (root->left->right):
void preOrder(struct node* root) {
    // Checks if the current node exists:
    if(root != NULL) {
        // Firstly, prints the value of the node:
        printf("%s ", root->value);
        // Then travels recursively the left side:
        preOrder(root->left);
        // Lastly, travels recursively the right side:
        preOrder(root->right);
    }
}

// In order, visits first the left side, then the root, and lastly the right side.
// Travels through the tree in order (left->root->right):
void inOrder(struct node* root) {
    // Checks if the current node exists:
    if (root != NULL) {
        // Firstly, travels recursively the left side:
        inOrder(root->left);
        // Then prints the value of the node:
        printf("%s ", root->value);
        // Lastly, travels recursively the right side:
        inOrder(root->right);
    }
}

// Post order, visits firstly the left side, then the right, and lastly the root.
// Travels through the tree in post order (left->right->root):
void postOrder(struct node* root) {
    // Checks if the current node exists:
    if(root != NULL) {
        // Firstly, travels recursively the left side:
        postOrder(root->left);
        // Then travels recursively the right side:
        postOrder(root->right);
        // Lastly, prints the value of the node:
        printf("%s ", root->value);
    }
}
