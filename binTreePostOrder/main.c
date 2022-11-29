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
    node * newNode = (node *) malloc(sizeof (node));
    newNode -> left = NULL;
    newNode -> right = NULL;
    newNode -> value = val;
    return newNode;
}

typedef struct stack {
    node ** elements;
    int top;
} stack;

stack * createStack(){
    stack * s1 = (stack *) malloc(sizeof (stack));
    s1 -> elements = (node **) malloc(MAXLIM * sizeof (node *));
    s1 -> top = -1;
    return s1;
}

void push(stack * s, node * n){
    if (s -> top == MAXLIM - 1){
        printf("\nStack Overflow");
        return;
    } else {
        s -> top++;
        s->elements [s ->top] = n;
    }
}

node * pop (stack *s){
    if (s -> top == -1){
        printf("\n Stack Underflow");
        return NULL;
    }
    node * tmp = s -> elements[s -> top];
    s -> top--;
    return tmp;
}

bool isStackEmpty (stack * s){
    if (s -> top == -1){
        return true;
    }
    return false;
}

void postOrderIterative (node * root) {

    /*
     * Push root to first stack.
2. Loop while first stack is not empty
   2.1 Pop a node from first stack and push it to second stack
   2.2 Push left and right children of the popped node to first stack
3. Print contents of second stack
     */
    //Creating 2 stacks;

    stack * s1 = createStack();
    stack * s2 = createStack();

    node * currentNode = root;

    push(s1, root);

    while (!isStackEmpty(s1)){

        currentNode = pop(s1);

        push(s2, currentNode);

        if (currentNode -> left != NULL) push(s1, currentNode->left);

        if (currentNode -> right != NULL) push (s1, currentNode -> right);
    }

    while (!isStackEmpty(s2)){
        node * tmp = pop(s2);
        printf(" %d ", tmp ->value);
    }

}

void postOrderRecursive(node * root){
    if (root == NULL){
        return;
    }
    postOrderRecursive(root -> left);
    postOrderRecursive(root -> right);
    printf(" %d ", root -> value);
}


int main() {
    node * root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);
    //postOrderRecursive(root);
    postOrderIterative(root);
    return 0;
}
