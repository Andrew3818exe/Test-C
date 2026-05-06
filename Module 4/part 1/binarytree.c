// This file is more of a basic representation of how a binary tree is formed, and
// how to calculate both the total height of the tree, and the depth of a node that
// we are searching, if it exists.
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

// Function that calculates the height of the tree:
int height(struct node* root) {
    // Checks if the tree is empty or in the leaf, returning 0
    if(root == NULL) {
        return 0;
    }
    // Calculates recursively the height of the sub-tree on the left side:
    int hgt_left = height(root->left);
    // Calculates recursively the height of the sub-tree on the right side:
    int hgt_right = height(root->right);
    // Returns 1 (root) + highest height value between left and right, reading:
    // "If hgt_left > hgt_right, return 1 + hgt_left, else, return 1 + hgt_right"
    return 1 + (hgt_left > hgt_right ? hgt_left : hgt_right);
}

// Function that calculates the depth of a specific node:
int depth(struct node* root, struct node* target, int level) {
    // Returns -1 if the target wasn't found / doesn't exist on this tree:
    if(root == NULL) {
        return -1;
    }
    // Returns the level after conlcuding that the node found is the target:
    if(root == target) {
        return level;
    }
    // Searches recursively on the left sub-tree, gradativelly increasing the level:
    int left = depth(root->left, target, level+1);
    // If it finds on the left sub-tree, returns the depth:
    if(left != -1) {
        return left;
    }
    // If it hasn't been found on the left, searches on the right:
    // Also returns the found value, or -1 if not.
    return depth(root->right, target, level+1);
}
