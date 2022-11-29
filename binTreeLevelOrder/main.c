#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXLIM 20

typedef struct node {
    int value;
    struct node * left;
    struct node * right;
}node;

node * createNode(int val){
    node * tmp = (node *) malloc(sizeof(node));
    tmp -> left = NULL;
    tmp -> right = NULL;
    tmp ->value = val;
    return tmp;
}

int height (node * root){
    if (root == NULL) return 0;

    int lHeight = height(root -> left);
    int rHeight = height(root -> right);

    if (lHeight > rHeight) {
        return (lHeight + 1);
    } else {
        return (rHeight + 1);
    }
}


void levelWiseNodesPrint(node * root, int currentLevel, bool isLeftToRight){
    //Handling base case.
    if (root == NULL){
        return;
    }

    if (currentLevel == 1){
        printf(" %d ", root -> value);
    }

    else if (currentLevel > 1){
        if (isLeftToRight){
            levelWiseNodesPrint(root -> left, currentLevel-1, isLeftToRight);
            levelWiseNodesPrint(root -> right, currentLevel-1, isLeftToRight);
        } else {
            levelWiseNodesPrint(root -> right, currentLevel-1, isLeftToRight);
            levelWiseNodesPrint(root -> left, currentLevel-1, isLeftToRight);
        }
    }
}

void printoutSpirally(node * root){
    int heightOfTree = height(root);
    int lvlIdx;
    bool isLeftToRight = true;

    for(lvlIdx = 0; lvlIdx <= heightOfTree; lvlIdx++){
        levelWiseNodesPrint(root, lvlIdx, isLeftToRight);
        isLeftToRight = !isLeftToRight;
    }
}


int main() {
     node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(7);
    root->left->right = createNode(6);
    root->right->left = createNode(5);
    root->right->right = createNode(4);
    printf("Spiral Order traversal of "
           "binary tree is \n");

    printoutSpirally(root);
    return 0;
}
