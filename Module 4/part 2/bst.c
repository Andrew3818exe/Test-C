// This file introduces the searching method for the binary tree, BST, with some functions,
// and an example, and another function that removes a node from a tree, with all possible
// scenarios (despite not being used in this example).
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct of the node:
typedef struct {
    char value[50];
    struct node* left;
    struct node* right;
} node;

// Function that prints all values in order (left->root->right):
void inOrder(node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%s, ", root->value);
        inOrder(root->right);
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

// Function that automatically inserts string values alphabetically:
node* insert(node* root, const char* value) {
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

// Function that carefully removes a value from the tree, with 3 possible scenarios:
node* remove(node* root, const char* value) {
    if(root == NULL) {
        return NULL; // Checks if the tree is empty or if it's not found / has been removed.
    }
    // Searches for the node to be removed.
    if(strcmp(value, root->value) < 0) {
        root->left = remove(root->left, value);
    } else if(strcmp(value, root->value) > 0) {
        root->right = remove(root->right, value);
    } else {
        // Scenario 1: Node has no children:
        // Removes the node and returns NULL.
        if(root->left == NULL && root->right == NULL) {
            free(root->value); // Frees the memory allocated dinamically.
            free(root);
            return NULL;
        // Scenario 2: Node has one children:
        // Switches the children's place with the node.
        } else if(root->left == NULL) {
            node* temp = root->right;
            free(root->value);
            free(root);
            return temp;
        } else if(root->right == NULL) {
            node* temp = root->left;
            free(root->value);
            free(root);
            return temp;
        // Scenario 3: Node has two children:
        // Searches the smallest string on the right sub tree (in alphabetical order), and switches with the atual node.
        } else {
            node* temp = root->right;
            while(temp->left != NULL) {
                temp = temp->left;
            }
            free(root->value);
            root->value = strdup(temp->value); // Copies the successor's string
            root->right = remove(root->right, temp->value);
        }
    }
    return root;
}

// Function that searches a key (string) in a binary tree (BST):
// Returns 1 if it finds it, 0 if not.
int search(node* root, const char* key) {
    if(root == NULL) {
        return 0; // In case it it's empty or doesn't exist.
    }

    if(strcmp(key, root->value) == 0) {
        return 1; // If the atual node is the key, you found it.
    } else if(strcmp(key, root->value) < 0) {
        return search(root->left, key); // If the key is less than the node's value, search on the left sub tree.
    } else {
        return search(root->right, key); // If the key is greater than the node's value, search on the right sub tree.
    }
}

int main() {
    node* root = NULL;
    root = insert(root, "Mud footsteps");
    root = insert(root, "Lost key");
    root = insert(root, "Book with a missing page");
    root = insert(root, "Dirty blanket");
    root = insert(root, "Lost drawer");

    printf("\nElements in order: ");
    inOrder(root);

    printf("\nSearching for 'Dirty blanket': %s", search(root, "Dirty blanket") ? "Found" : "Not found");
    printf("\nSearching for 'Glasses': %s", search(root, "Glasses") ? "Found" : "Not found");

    return 0;
}
