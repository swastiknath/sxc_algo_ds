#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAXLIM 20

typedef struct bstNode {
    int value;
    struct bstNode * left;
    struct bstNode * right;
    struct bstNode * parent;

}bstNode;

bstNode * createNewBSTNode(int val){
    bstNode * newbstNode = (bstNode *) malloc (sizeof (bstNode));
    newbstNode -> left = NULL;
    newbstNode -> right = NULL;
    newbstNode -> value = val;
    return newbstNode;
}



bstNode * insertNodeIntoBST(bstNode * root, int val){
    if (root == NULL){
        return createNewBSTNode(val);
    }
    else {
        bstNode * bn;
        if (val <= root ->value){
            // Go left;
            bn = insertNodeIntoBST(root ->left, val);
            root -> left = bn;
            bn -> parent = root;
        } else {
            bn = insertNodeIntoBST(root -> right, val);
            root -> right = bn;
            bn -> parent = root;
        }
    }
    return root;
}

void inorder (bstNode * root){
    if (root == NULL){
        return;
    }
    inorder(root -> left);
    printf(" %d ", root -> value);
    inorder(root -> right);
}


bstNode * getMinimumNode(bstNode * root){
    bstNode *current = root;
    while (current -> left != NULL){
        current = current -> left;
    }
    return current;
}

bstNode * findInorderSuccessor (bstNode * root, bstNode * givenNode){
    //if the right subtree of the node of is not null,
    // then the leftmost node of the right subtree will be the inorder successor.
    if (givenNode -> right != NULL){
       return getMinimumNode(givenNode -> right);

    }
    bstNode * successor = NULL;
    while (root != NULL){
        if (givenNode -> value < root->value){
            successor = root;
            root = root -> left;
        } else if (givenNode -> value > root -> value){
            root = root -> right;
        } else {
            break;
        }
    }
    return successor;
}


int main() {
    bstNode * root = NULL;
    bstNode * successor = NULL;

    root = insertNodeIntoBST(root, 50);
    root = insertNodeIntoBST(root, 70);
    root = insertNodeIntoBST(root, 5);
    root = insertNodeIntoBST(root, 34);
    root = insertNodeIntoBST(root, 89);
    root = insertNodeIntoBST(root, 15);
    root = insertNodeIntoBST(root, 10);
    root = insertNodeIntoBST(root, 11);
    root = insertNodeIntoBST(root, 17);

    bstNode * givenNode = root->left->right;
    successor = findInorderSuccessor(root, givenNode);
    printf("\n%d - Successor is %d\n", givenNode ->value, successor ->value);
    inorder(root);

    return 0;
}
