// This file shows a simple way of working with hash table, creating one, using functions
// to either insert, search or remove a name from a table, with some examples after it.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Struct of a node inside the list:
typedef struct Node {
    char name[50];
    struct Node* next; // Pointer to the next node
} Node;

// The hash table is an array of pointers to the node:
Node* hashTable[TABLE_SIZE];

// Function that transforms a string name into an index to the array:
int hashFunction(const char* key) {
    int sum = 0;
    for(int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return sum % TABLE_SIZE;
}

// Function that inserts a name, creating a node and adding to the start of the nested list:
void insert(const char* name) {
    int idx = hashFunction(name); // Discovers where to slot the name
    
    // Creates a node:
    Node* new = (Node*) malloc(sizeof(Node));
    strcpy(new->name, name);
    
    // Inserts at the start of the list (head):
    new->next = hashTable[idx];
    hashTable[idx] = new;
}

// Function that searches where it compares names until finds it, or not:
Node* search(const char* name) {
    int idx = hashFunction(name);
    Node* atual = hashTable[idx];

    while(atual != NULL) {
        if(strcmp(atual->name, name) == 0) {
            return atual; // Found
        }
        atual = atual->next;
    }
    return NULL; // Not in list
}

// Function that removes carefully a name from the list, by making the list still function with pointers normally:
void Remove(const char* name) {
    int idx = hashFunction(name);
    Node* atual = hashTable[idx];
    Node* previous = NULL;

    while(atual != NULL) {
        if(strcmp(atual->name, name) == 0) {
            if(previous == NULL) {
                hashTable[idx] = atual->next; // Was the first
            } else {
                previous->next = atual->next; // "Skips" the atual node
            }
            free(atual);
            printf("'%s' removed.\n", name);
            return;
        }
        previous = atual;
        atual = atual->next;
    }
    printf("'%s' not found.\n", name);
}

int main() {

    insert("Ana");
    insert("Bruno");
    insert("Carlos"); // Can collide with "Ana"
    insert("Amanda"); // Can collide with "Bruno"

    printf("Searching 'Bruno': %s\n", search("Bruno") ? "Found" : "Not found");

    printf("Searching 'John': %s\n", search("John") ? "Found" : "Not found");

    Remove("Carlos");
    Remove("John");
    return 0;
}
