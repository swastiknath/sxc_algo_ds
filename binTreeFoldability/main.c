#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

typedef struct node {
    int value;
    struct node * left;
    struct node * right;
} node;

node * createNewNode(int val){
    node * temp = (node *) malloc(sizeof(node));
    temp -> left = NULL;
    temp -> right = NULL;
    temp -> value = val;
    return temp;
}

// Trees will be called Foldable if the subtrees are mirror image of each other.

bool checkFoldabilityOfSubtrees(node * leftSubTree, node * rightSubTree){

    if (leftSubTree == NULL && rightSubTree == NULL) return true;
    if (leftSubTree == NULL || rightSubTree == NULL) return false;

    return checkFoldabilityOfSubtrees(leftSubTree ->left, rightSubTree -> right)
    && checkFoldabilityOfSubtrees(leftSubTree -> right , rightSubTree -> left);
}

bool isFoldableBinaryTree (node * root){
    // Handling base cases.
    if (root == NULL) {
        return true;
    }
    // Check Foldability of both the subtrees from the root.
    return checkFoldabilityOfSubtrees(root -> left, root -> right);
}
int main() {
    node* root = createNewNode(1);
    root->left = createNewNode(2);
    root->right = createNewNode(3);
    root->left->right = createNewNode(4);
    root->right->left = createNewNode(5);

    if (isFoldableBinaryTree(root)){
        printf("\nFoldable Binary Tree");
    } else {
        printf("\nNot Foldable Binary Tree");

    }
    return 0;
}
