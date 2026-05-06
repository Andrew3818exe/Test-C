// This file is a basic representation of what a binary tree looks like, combining
// the past structures of a tree (files binarytree.c and route.c) and implementing
// new ones, such as dinamic memory allocation, in one.
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
        printf("%s, ", root->value);
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
        printf("%s, ", root->value);
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
        printf("%s, ", root->value);
    }
}

// Function that will create and initialize a new node of the binary tree, inserting the received value:
struct node* createNode(char* value) {
    // Allocate dinamically memory to a new node and stores the address in 'new':
    struct node* new = (struct node*) malloc(sizeof(struct node));
    
    // Copy the value passed as parameter (string) to the 'value' of the node:
    strcpy(new->value, value);

    // Initialize the pointers for the left and right side as NULL (no values inserted yet):
    new->left = NULL;
    new->right = NULL;

    // Returns the address of the new node:
    return new;
}

// Function that frees all the allocated memory to the binary tree recursively:
void freeTree(struct node* root) {
    // Checks if the atual node exists:
    if(root != NULL) {
        // Firstly frees the left sub tree:
        freeTree(root->left);
        // Then frees the right sub tree:
        freeTree(root->right);
        // Lastly, frees the atual note:
        free(root);
    }
}

int main() {
    // Creates the node root of the tree, represented by "Main Hall":
    struct node* root = createNode("Main Hall");

    // Connects "Living Room" to the left side of the root:
    root->left = createNode("Living Room");

    // Connects the node "Library" to the right side of the root:
    root->right = createNode("Library");

    // "Bedroom" to the left side of "Living Room":
    root->left->left = createNode("Bedroom");

    // Shows the elements of the tree in pre order (root->left->right):
    printf("Pre order: ");
    preOrder(root);
    printf("\n");

    // Shows the elements of the tree in order(left->root->right):
    printf("In order: ");
    inOrder(root);
    printf("\n");

    // Shows the elements of the tree in post order(left->right->root):
    printf("Post order: ");
    postOrder(root);
    printf("\n");

    // Frees all the allocated memory of the tree:
    freeTree(root);

    // Tells the program that the code executed successfully:
    return 0;
}
