#include <stdio.h>
#include <stdbool.h>
#include<stdlib.h>
#define MAXLIM 30

typedef struct node {
    int value;
    struct node * left;
    struct node * right;
}node;

node * createNode (int val){
    node * newNode = (node *) malloc (sizeof(node));
    newNode -> left = NULL;
    newNode -> right = NULL;
    newNode -> value = val;
    return newNode;
}

typedef struct nodeVector {

    node ** elements;
    int top; // to get the size of the element.

} nodeVector;

nodeVector * createNodeVector() {
    nodeVector  * vectTemp = (nodeVector *) malloc(sizeof (nodeVector));
    vectTemp -> elements = (node **) malloc(MAXLIM * sizeof (node *));
    vectTemp -> top = -1;
    return vectTemp;
}

void push (nodeVector * v, node * n){
    if (v -> top == MAXLIM - 1) {
        printf("\nOverflow");
        return;
    }
    v -> top++;
    v ->elements [v -> top] = n;
}

node * pop(nodeVector * v, node *n){
    if (v -> top == -1){
        printf ("\nUnderflow");
        return NULL;
    }
    node * temp = v->elements[v -> top];
    v -> top--;
    return temp;
}

nodeVector * getAllTrees (int * inOrderArr, int start, int end){
    nodeVector  * nv = createNodeVector();
    int inArrIdx, lTreeIdx, rTreeIdx;

    // Handling Base Case
    if (start > end){
        push (nv, NULL);
        return nv;
    }

    for (inArrIdx = start; inArrIdx <= end; inArrIdx++){
        nodeVector  * lTreeNodes = getAllTrees(inOrderArr, start, inArrIdx - 1);
        nodeVector * rTreeNodes = getAllTrees(inOrderArr, inArrIdx + 1, end);

        for (lTreeIdx = 0; lTreeIdx <= lTreeNodes -> top; lTreeIdx++){
            for (rTreeIdx = 0; rTreeIdx <= rTreeNodes -> top; rTreeIdx++){
                node * root = createNode(inOrderArr[inArrIdx]);
                root -> left = lTreeNodes ->elements [lTreeIdx];
                root -> right = rTreeNodes -> elements[rTreeIdx];
                push (nv, root);
            }
        }
    }
    return nv;
}

void preOrder(node * root){

    if (root == NULL){
        return;
    }
    printf(" %d ", root -> value);
    preOrder(root -> left);
    preOrder(root -> right);
}

int main() {
    int in[] = {4, 5, 7};
    int n = sizeof(in) / sizeof(in[0]);

    nodeVector * treesList = getAllTrees(in, 0, n - 1);
    int idx;
    for (idx = 0; idx <= treesList ->top; idx++){
        preOrder(treesList -> elements[idx]);
        printf("\n");
    }
    return 0;
}
