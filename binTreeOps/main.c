#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node * left;
    struct node * right;
}node ;

struct node * newNode (int val){
    node * newN = (struct node *) malloc(sizeof(struct node));
    newN -> left = NULL;
    newN -> right = NULL;
    newN -> value = val;

    return newN;
}

int findMax(int a, int b){
    return (a > b) ? a : b;
}

int findHeight (node * n){
    // Base Height will be 0, if there are no nodes;
    if (n == NULL){
        return 0;
    }
    // Max Height Between the left and right subtree.
    return 1 + findMax(findHeight(n -> left), findHeight(n -> right));
}


/*
 *
 * Finding the diameter of the Tree:
 * 1. Get the height of the left or right subtree.
 * 2. Get the diameter of the left or right subtree.
 * 3. Return the maximum of the following three:
 *         -> Diameter of the left subtree.
 *         -> Diameter of the right subtree.
 *         -> Height of the left subtree or right subtree or 1+left_height + right_height;
 *
 */


int findDiameter(node * tree){
    if (tree == NULL){
        return 0;
    }

    int lHeight = findHeight(tree -> left);
    int rHeight = findHeight(tree -> right);

    int lDiameter = findDiameter(tree -> left);
    int rDiameter = findDiameter(tree -> right);

    return findMax(findMax(lDiameter, rDiameter), 1+lHeight+rHeight);
}

int main() {
    node * root = newNode(14);
    root -> left = newNode(16);
    root -> right = newNode(22);

    root -> left -> left = newNode(27);
    root -> left -> right = newNode(36);

    root -> right -> left = newNode(33);
    root -> right -> right = newNode (20);

    root -> left -> left -> left = newNode(30);

    printf("\n Diameter of the Tree is: %d", findDiameter(root));
}
