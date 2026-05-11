// This file, differently from the previous one, has a difference inside the insert function,
// Because instead of making a nested list, it puts the new value to the next available spot
// on the list, with a different index, same goes for searching.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// Struct that represents an entrance to the table:
typedef struct {
    char name[50];
    int occupied; // 0 = free, 1 = occupied, 2 = removed
} Entrance;

Entrance hashTable[TABLE_SIZE];

// Simple hash function that transforms the string into an index:
int hashFunction(const char* key) {
    int sum = 0;
    for(int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return sum % TABLE_SIZE;
}

// Function that inserts the names into the desired index values in the list, and if it's occupied,
// it searches for the next free slot to put in:
void insert(const char* name) {
    int idx = hashFunction(name);
    for(int i = 0; i < TABLE_SIZE; i++) {
        int pos = (idx + i) % TABLE_SIZE;

        // 0 = free, 1 = occupied, -1 = removed
        if(hashTable[pos].occupied == 0 || hashTable[pos].occupied == -1) {
            strcpy(hashTable[pos].name, name);
            hashTable[pos].occupied = 1;
            return;
        } 
    }
    printf("Full table. Not possible to insert '%s'\n", name);
}

// Function that searches the string value needed, that follows the same idea of the insert function:
int search(const char* name) {
    int idx = hashFunction(name);

    for(int i = 0; i < TABLE_SIZE; i++) {
        int pos = (idx + i) % TABLE_SIZE;

        if(hashTable[pos].occupied == 0) {
            return -1; // Stops: position never used
        }

        if(hashTable[pos].occupied == 1 && strcmp(hashTable[pos].name, name) == 0) {
            return pos; // Finds the string
        }

        return -1; // Not found
    }
}

// Function that removes the string and makes the position as removed (-1):
void Remove(const char* name) {
    int pos = search(name);
    if(pos == -1) {
        printf("'%s' Not found.\n", name);
        return;
    }

    hashTable[pos].occupied = -1;
    printf("'%s' removed.\n", name);
}

int main() {
    // Initializes the table:
    for(int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i].occupied = 0;
    }

    insert("Ana");
    insert("Bruno");
    insert("Carlos"); // Can collide with "Ana"
    insert("Amanda"); // Can collide with "Bruno"

    printf("Searching 'Bruno': %s\n", search("Bruno") != -1 ? "Found" : "Not found");
    printf("Searhcing 'John': %s\n", search("John") != -1 ? "Found" : "Not found");

    Remove("Carlos");
    Remove("John");

    return 0;
}
