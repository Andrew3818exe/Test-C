// This file combines both types of hash tables insertion and searching, while also
// adding the show list functions, and with an example with a bigger list of names.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Hash table with chaining:
// Struct for chaining:
typedef struct Node {
    char value[50];
    struct Node* next;
} Node;

// Hash table:
Node* chainingTable[TABLE_SIZE];

// Simple hash function:
int hashFunction(const char* key) {
    int sum = 0;
    for(int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return sum % TABLE_SIZE;
}

// Function that inserts a name, creating a node and adding to the start of the chaining list:
void insertChaining(const char* value) {
    int idx = hashFunction(value); // Discovers where to slot the name
    
    // Creates a node:
    Node* new = (Node*) malloc(sizeof(Node));
    strcpy(new->value, value);
    
    // Inserts at the start of the list (head):
    new->next = chainingTable[idx];
    chainingTable[idx] = new;
}

// Function that searches where it compares names until finds it, or not:
Node* searchChaining(const char* value) {
    int idx = hashFunction(value);
    Node* atual = chainingTable[idx];

    while(atual != NULL) {
        if(strcmp(atual->value, value) == 0) {
            return atual; // Found
        }
        atual = atual->next;
    }
    return NULL; // Not in list
}

// Function that removes carefully a name from the list, by making the list still function with pointers normally:
void removeChaining(const char* value) {
    int idx = hashFunction(value);
    Node* atual = chainingTable[idx];
    Node* previous = NULL;

    while(atual != NULL) {
        if(strcmp(atual->value, value) == 0) {
            if(previous == NULL) {
                chainingTable[idx] = atual->next; // Was the first
            } else {
                previous->next = atual->next; // "Skips" the atual node
            }
            free(atual);
            printf("'%s' removed.\n", value);
            return;
        }
        previous = atual;
        atual = atual->next;
    }
    printf("'%s' not found.\n", value);
}

// Function that shows the chaining table values:
void showChaining() {
    printf("\nHash table (Chaining):\n");

    for(int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);
        Node* atual = chainingTable[i];

        while(atual != NULL) {
            printf("%s -> \n", atual->value);
            atual = atual->next;
        }

        printf("NULL\n");
    }
}

// Hash table with linear insertion:
// Struct for entrance:
typedef struct {
    char value[50];
    int occupied; // 0 = free, 1 = occupied, -1 = removed;
} Entrance;

// Hash table:
Entrance linearTable[TABLE_SIZE];

// Function that inserts in linear order
void insertLinear(const char* value) {
    int idx = hashFunction(value);
    for(int i = 0; i < TABLE_SIZE; i++) {
        int pos = (idx + i) % TABLE_SIZE;

        // 0 = free, 1 = occupied, -1 = removed
        if(linearTable[pos].occupied == 0 || linearTable[pos].occupied == -1) {
            strcpy(linearTable[pos].value, value);
            linearTable[pos].occupied = 1;
            return;
        } 
    }
    printf("Full table. Not possible to insert '%s'\n", value);
}

// Function that searches the string value needed, that follows the same idea of the insert linear function:
int searchLinear(const char* value) {
    int idx = hashFunction(value);

    for(int i = 0; i < TABLE_SIZE; i++) {
        int pos = (idx + i) % TABLE_SIZE;

        if(linearTable[pos].occupied == 0) {
            return -1; // Stops: position never used
        }

        if(linearTable[pos].occupied == 1 && strcmp(linearTable[pos].value, value) == 0) {
            return pos; // Finds the string
        }
    }

    return -1; // Not found
}

// Function that removes the string and makes the position as removed (-1):
void removeLinear(const char* value) {
    int pos = searchLinear(value);
    if(pos == -1) {
        printf("'%s' Not found.\n", value);
        return;
    }

    linearTable[pos].occupied = -1;
    printf("'%s' removed.\n", value);
}

// Function that shows the linear table values:
void showLinear() {
    printf("\nHash table (Linear probing):\n");

    for(int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);

        if(linearTable[i].occupied == 1) {
            printf("%s\n", linearTable[i].value);
        } else if(linearTable[i].occupied == -1) {
            printf("<removed>\n");
        } else {
            printf("<empty>\n");
        }
    }
}

int main() {

    printf("\n");
    
    // Initialize the tables:
    for(int i = 0; i < TABLE_SIZE; i++) {
        chainingTable[i] = NULL;
        linearTable[i].occupied = 0;
    }

    // Examples of words:
    const char* words[] = {
        "Ana", "Bruno", "Carlos", "Amanda", "Paulo",
        "Lucas", "Marina", "Joana", "Roberta", "Clara", "Daniel"
    };

    int n = sizeof(words) / sizeof(words[0]);

    // Insertion in the two tables:
    for(int i = 0; i < n; i++) {
        insertChaining(words[i]);
        insertLinear(words[i]);
    }

    // Visualization of both lists after insertion:
    showChaining();
    showLinear();

    // Search for some names:
    printf("\nSearching 'Bruno' (chaining): %s\n", searchChaining("Bruno") ? "Found" : "Not found");
    printf("Searching 'Joana' (linear): %s\n", searchLinear("Joana") ? "Found" : "Not found");
    printf("Searching 'Zeca' (chaining): %s\n", searchChaining("Zeca") ? "Found" : "Not found");

    // Removing some names:
    removeChaining("Carlos");
    removeLinear("Carlos");
    // Testing non-existant names:
    removeChaining("Zeca");
    removeLinear("Zeca");

    // Final visualization of the tables:
    showChaining();
    showLinear();

    // Freeing memory from chaining table:
    for(int i = 0; i < TABLE_SIZE; i++) {
        Node* atual = chainingTable[i];
        while(atual != NULL) {
            Node* temp = atual;
            atual = atual->next;
            free(temp);
        }
    }

    return 0;
}
