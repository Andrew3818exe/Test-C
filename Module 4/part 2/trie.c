// This file is another way of creating a tree and searcihng withing it, differently from
// the previous one, where this one sorts alphabetically as well, but creates new nodes
// only from existing ones, and checks if that word has ended or not, and has a function
// that makes output only lowercased words.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Struct of the node:
typedef struct NodeTrie {
    struct NodeTrie* children[ALPHABET_SIZE];
    bool isWordEnd; // Checks if the last letter is truly the end of the string.
} NodeTrie;

// Function that creates a node:
NodeTrie* createNode() {
    NodeTrie* newNode = (NodeTrie*) malloc(sizeof(NodeTrie));
    newNode->isWordEnd = false;
    for(int i = 0; i < ALPHABET_SIZE; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Function that inserts the word inside the tree in it's roots:
void insert(NodeTrie* root, const char* word) {
    NodeTrie* atual = root;
    for(int i = 0; word[i] != '\0'; i++) {
        int idx = word[i] - 'a'; // Transforms letters in index from 0 - 25 representing each letter of the alphabet.
        if(atual->children[idx] == NULL) {
            atual->children[idx] = createNode();
        }
        atual = atual->children[idx];
    }
    atual->isWordEnd = true;
}

// Function that searches for the word wanted:
bool search(NodeTrie* root, const char* word) {
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
        printf("%s\n", buffer);
    }

    for(int i = 0; i < ALPHABET_SIZE; i++) {
        if(node->children[i] != NULL) {
            buffer[level] = 'a' + i;
            listWords(node->children[i], buffer, level + 1);
        }
    }
}

// Function that converts words into only lowercased letters:
// This is important because from 'a' to 'z' there are 26 letters (the size of ALPHABETIC_SIZE)
// and if we use other symbols or uppercase letters, it will output errors.
void normalized(const char* input, char* output) {
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

int main() {
    NodeTrie* root = createNode();
    char normalize[100];

    normalized("Mud footsteps", normalize);
    insert(root, normalize);

    normalized("Lost key", normalize);
    insert(root, normalize);

    normalized("Book with missing page", normalize);
    insert(root, normalize);

    normalized("Dirty blanket", normalize);
    insert(root, normalize);

    normalized("Lost drawer", normalize);
    insert(root, normalize);

    char buffer[100];
    listWords(root, buffer, 0);

    return 0;
}
