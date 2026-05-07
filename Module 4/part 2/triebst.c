// This file combines both functionalities of BST (bst.c) and Trie (trie.c) into one single
// code file, with examples, and some polishments on some functions.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

// --------------- BST ---------------
// Struct for BST:
typedef struct NodeBST {
    char value[50];
    struct NodeBST* left;
    struct NodeBST* right;
} NodeBST;

// Function that will create and initialize a new node of the binary tree, inserting the received value:
NodeBST* createNodeBST(const char* value) {
    // Allocate dinamically memory to a new node and stores the address in 'new':
    NodeBST* new = (NodeBST*) malloc(sizeof(NodeBST));
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

// Function that automatically inserts string values alphabetically on BST:
NodeBST* insertBST(NodeBST* root, const char* value) {
    // If the tree (or sub tree) is empty, creates a new node:
    if(root == NULL) {
        return createNodeBST(value);
    }

    if(strcmp(value, root->value) < 0) {
        // Inserts on the left sub tree:
        root->left = insertBST(root->left, value);
    } else {
        // Inserts on the right sub tree:
        root->right = insertBST(root->right, value);
    }
    return root;
}

// Function that searches a key (string) in a binary tree (BST):
// Returns 1 if it finds it, 0 if not.
int searchBST(NodeBST* root, const char* key) {
    if(root == NULL) {
        return 0; // In case it it's empty or doesn't exist.
    }

    if(strcmp(key, root->value) == 0) {
        return 1; // If the atual node is the key, you found it.
    } else if(strcmp(key, root->value) < 0) {
        return searchBST(root->left, key); // If the key is less than the node's value, search on the left sub tree.
    } else {
        return searchBST(root->right, key); // If the key is greater than the node's value, search on the right sub tree.
    }
}

// Function that prints all values from BST in order (left->root->right):
void inOrderBST(NodeBST* root) {
    if (root != NULL) {
        inOrderBST(root->left);
        printf("%s, ", root->value);
        inOrderBST(root->right);
    }
}

// Function that frees all the allocated memory to the binary tree recursively:
void freeBST(NodeBST* root) {
    // Checks if the atual node exists:
    if(root != NULL) {
        // Firstly frees the left sub tree:
        freeBST(root->left);
        // Then frees the right sub tree:
        freeBST(root->right);
        // Lastly, frees the atual note:
        free(root);
    }
}

// --------------- Trie ---------------
// Struct for Trie:
typedef struct NodeTrie {
    struct NodeTrie* children[ALPHABET_SIZE];
    bool isWordEnd;
} NodeTrie;

// Function that creates a Trie node:
NodeTrie* createNodeTrie() {
    NodeTrie* newNode = (NodeTrie*) malloc(sizeof(NodeTrie));
    newNode->isWordEnd = false;
    for(int i = 0; i < ALPHABET_SIZE; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Function that converts words into only lowercased letters:
void normalize(const char* input, char* output) {
    int j = 0;
    for(int i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        if(c >= 'A' && c <= 'Z') {
            c += 32; // Converts to lowercased letters.
        }
        if(c >='a' && c <= 'z') {
            output[j++] = c; // Keeps only letters (no other symbols and space).
        }
    }
    output[j] = '\0';
}

// Function that inserts the word inside the trie in it's roots:
void insertTrie(NodeTrie* root, const char* word) {
    NodeTrie* atual = root;
    for(int i = 0; word[i] != '\0'; i++) {
        int idx = word[i] - 'a'; // Transforms letters in index from 0 - 25 representing each letter of the alphabet.
        if(atual->children[idx] == NULL) {
            atual->children[idx] = createNodeTrie();
        }
        atual = atual->children[idx];
    }
    atual->isWordEnd = true;
}

// Function that searches for the word wanted in trie:
bool searchTrie(NodeTrie* root, const char* word) {
    NodeTrie* atual = root;
    for(int i = 0; word[i] != '\0'; i++) {
        int idx = word[i] - 'a'; // Checks for the word searched.
        if(atual->children[idx] == NULL) {
            return false; // Returns false if it hasn't been found.
        }
        atual = atual->children[idx];
    }
    return atual != NULL && atual->isWordEnd; // Returns the word if it has been found.
}

// Void that lists all the words inside the tree, in pre order alphabetically:
void listWords(NodeTrie* node, char* buffer, int level) {
    if(node->isWordEnd) {
        buffer[level] = '\0';
        printf("%s, ", buffer);
    }

    for(int i = 0; i < ALPHABET_SIZE; i++) {
        if(node->children[i] != NULL) {
            buffer[level] = 'a' + i;
            listWords(node->children[i], buffer, level + 1);
        }
    }
}

// Function that frees all the allocated memory to the trie recursively:
void freeTrie(NodeTrie* node) {
    for(int i = 0; i < ALPHABET_SIZE; i++) {
        if(node->children[i] != NULL) {
            freeTrie(node->children[i]);
        }
    }
    free(node);
}

int main() {
    // ---- BST ----
    printf("\n==== BST ====\n");
    NodeBST* rootBST = NULL;
    rootBST = insertBST(rootBST, "Mud footsteps");
    rootBST = insertBST(rootBST, "Lost keys");
    rootBST = insertBST(rootBST, "Book with missing page");
    rootBST = insertBST(rootBST, "Dirty blanket");
    rootBST = insertBST(rootBST, "Lost drawer");

    printf("In order (BST): ");
    inOrderBST(rootBST);
    printf("\nSearch 'Dirty blanket' (BST): %s\n", searchBST(rootBST, "Dirty blanket") ? "Found" : "Not found");
    printf("Search 'Glasses' (BST): %s\n", searchBST(rootBST, "Glasses") ? "Found" : "Not found");

    // ---- Trie ----
    printf("\n==== Trie ====\n");
    NodeTrie* rootTrie = createNodeTrie();
    char normalized[100];

    normalize("Mud footsteps", normalized);
    insertTrie(rootTrie, normalized);
    normalize("Lost keys", normalized);
    insertTrie(rootTrie, normalized);
    normalize("Book with missing page", normalized);
    insertTrie(rootTrie, normalized);
    normalize("Dirty blanket", normalized);
    insertTrie(rootTrie, normalized);
    normalize("Lost drawer", normalized);
    insertTrie(rootTrie, normalized);

    printf("Trie words: ");
    char buffer[100];
    listWords(rootTrie, buffer, 0);
    printf("\n");
    normalize("Dirty blanket", normalized);
    printf("Search 'dirtyblanket' (Trie): %s\n", searchTrie(rootTrie, normalized) ? "Found" : "Not found");
    normalize("Glasses", normalized);
    printf("Search: 'glasses' (Trie): %s\n", searchTrie(rootTrie, normalized) ? "Found" : "Not found");

    // Freeing memory allocated:
    freeBST(rootBST);
    freeTrie(rootTrie);

    return 0;
}
