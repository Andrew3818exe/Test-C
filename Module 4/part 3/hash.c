// This file is just a simple introduction to hash table, and has no functionalities
// for a Main function, as it's just to show the basics of a hash table.
#include <stdio.h>
#include <string.h>

// Simple hash function that adds characters' values (from ASCII table) and the use of %:
int simpleHash(const char* str, int table_size) {
    int sum = 0;
    for(int i = 0; str[i != '\0'; i++]) {
        sum += str[i];
    }
    return sum % table_size;
}

// Compound hash function that multiplies the ASCII value with the position of the letter of the word:
int compoundHash(const char* str, int table_size) {
    int hash = 0;
    for(int i = 0; str[i] != '\0'; i++) {
        hash += str[i] (i + 1);
    }
    return hash % table_size;
}
