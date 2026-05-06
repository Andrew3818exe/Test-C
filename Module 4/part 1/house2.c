// The difference from this code to the previous one, is that instead of manually
// inserting the values where I want, a function was created to automatically
// insert the values that was passed to the functions, in alphabetical order.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The structure of a node on a binary tree:
typedef struct{
    // Name or value of the node:
    char value[50];

    // Pointer to the left side:
    struct node* left;
    // Pointer to the right side:
    struct node* right;
} node;

// Pre order, visits the main node first (root), then the left side, and lastly the right side.
// Travels through the tree in pre order (root->left->right):
void preOrder(node *root) {
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
void inOrder(node *root) {
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
void postOrder(node *root) {
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
node* createNode(const char* value) {
    // Allocate dinamically memory to a new node and stores the address in 'new':
    node* new = (node*) malloc(sizeof(node));
    // Ends the program in case of memory error:
    if(new == NULL) {
        printf("Error on allocating memory.");
        exit(1);
    }
    
    // Copy the value passed as parameter (string) to the 'value' of the node:
    strcpy(new->value, value);

    // Initialize the pointers for the left and right side as NULL (no values inserted yet):
    new->left = NULL;
    new->right = NULL;

    // Returns the address of the new node:
    return new;
}

// Function that will insert a value on the tree recursively, in alphabetic order:
// If value < atual node -> goes to the left side
// If value >= atual node -> goes to the right side
node* insert(node *root, const char* value) {
    // If the tree (or sub tree) is empty, creates a new node:
    if(root == NULL) {
        return createNode(value);
    }

    if(strcmp(value, root->value) < 0) {
        // Inserts on the left sub tree:
        root->left = insert(root->left, value);
    } else {
        // Inserts on the right sub tree:
        root->right = insert(root->right, value);
    }
    return root;
}

// Function that frees all the allocated memory to the binary tree recursively:
void freeTree(node *root) {
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
    // Starts the tree empty:
    node* root = NULL;

    // Inserts elements on the tree (as example):
    root = insert(root, "Main Hall");
    root = insert(root, "Living Room");
    root = insert(root, "Library");
    root = insert(root, "Bedroom");

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
