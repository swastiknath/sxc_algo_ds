#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXLIM 20

typedef struct node {
    int value;
    struct node * left;
    struct node * right;
}node;

node * createNode (int val){
    node * newNode = (node *) malloc(sizeof(node));
    newNode ->left = NULL;
    newNode -> right = NULL;
    newNode -> value = val;
    return newNode;
}

typedef struct stack {
    node ** elements;
    int top;
} stack;

stack * createStack(){
    stack * newStack = (stack *) malloc(sizeof (stack));
    newStack -> elements = (node **) malloc(MAXLIM * sizeof (node *));
    newStack -> top = -1;
    return newStack;
}

void push (stack * s, node * n){
    if (s -> top == MAXLIM - 1){
        printf("\nStack Overflow");
        return;
    }
    s -> top++;
    s -> elements[s -> top] = n;
}

node * pop (stack * s){
    if (s -> top == -1){
        printf("\nStack Underflow.");
        return NULL;
    }
    node * temp = s -> elements[s -> top];
    s -> top--;
    return temp;
}

bool isStackEmpty(stack * s){
    if (s -> top == -1) return true;
    return false;
}

void inOrderIterative(node * root){
    // Initialize an empty stack
    stack * s = createStack();
    //initialize the current node as the root
    node * currentNode = root;

    // Repeat until the stack becomes empty and currentNode is NULL.
    while (!isStackEmpty(s) || currentNode != NULL){
        if (currentNode != NULL){
            push(s, currentNode);
            currentNode = currentNode -> left;
        }
        else {
            currentNode = pop(s);
            printf(" %d ", currentNode -> value);
            currentNode = currentNode -> right;
        }
    }
}


void inOrderRecursive (node * root){
    if (root == NULL){
        return;
    }
    inOrderRecursive(root ->left);
    printf(" %d ", root -> value);
    inOrderRecursive(root -> right);
}

// Pre-order Recursive.

void preOrderRecursive(node * root){

    stack * stack1 = createStack();
    node * temp = root;
    push(stack1, root);

    while (!isStackEmpty(stack1))
    {
        temp = pop(stack1);
        printf(" %d ", temp ->value);
        if (temp -> right) push(stack1, temp -> right);
        if (temp -> left) push(stack1, temp -> left);

    }

}

int main() {
    node *root = createNode(1);
    root->left        = createNode(2);
    root->right       = createNode(3);
    root->left->left  = createNode(4);
    root->left->right = createNode(5);

    preOrderRecursive(root);
    free(root);
    return 0;
}
