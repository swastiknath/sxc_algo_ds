#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#define MAXLIMIT 20

typedef struct node {
    int value;
    struct node * left;
    struct node * right;
} node;

node * createNewNode(int val) {
    node * newNode = (node *) malloc(sizeof (node));
    newNode -> left = NULL;
    newNode -> right = NULL;
    newNode -> value = val;
    return newNode;
}

typedef struct queue {
    node ** elements;
    int rear;
    int front;
} queue;

queue * createNewQueue () {
    queue * q = (queue *) malloc(sizeof(queue));
    q -> rear = -1;
    q -> front = -1;
    q -> elements = (node **) malloc(MAXLIMIT * sizeof (node));
    return q;
}

void push (queue * q, node * n){
    // in queue elements will be inserted from the last.
    if (q -> rear == MAXLIMIT - 1){
        printf("Queue Overflow");
        return;
    }

    else if (q -> front == -1 || q -> rear == -1){
        q -> rear++;
        q -> front++;
        q -> elements[q->rear] = n;
    }

    else{
        q -> rear++;
        q -> elements[q->rear] = n;
    }


}

node * pop (queue * q){

    if (q -> front == -1 || q-> front > q -> rear) {
        printf("\nQueue Underflow.");
        return NULL;
    } else {
        node * temp = q -> elements[q->front];
        q -> front++;
        return temp;
    }
}

bool isQueueEmpty(queue * q){
    if(q -> front == -1 || q -> front > q -> rear){
        return true;
    } else {
        return false;
    }
}


node * insertIntoTree(node * tree, queue * q, int val){
    //Insert a New Tree Node with Level Order Traversal.

    if (tree == NULL){
        tree = createNewNode(val);
        return tree;
    }

    // Pushing the Root into the Queue.
    push(q, tree);

    while (!isQueueEmpty(q)){
        node * temp = pop(q);
        if(temp -> left != NULL){
            push(q, temp->left);
        } else {
            temp -> left = createNewNode(val);
            return tree;
        }

        if (temp -> right != NULL){
            push (q, temp -> right);
        } else {
            temp -> right = createNewNode(val);
            return tree;
        }
    }
}

void inOrderTraversal (node * tree){
    if (tree == NULL ){
        return;
    }

    inOrderTraversal(tree -> left);
    printf(" %d ", tree -> value);
    inOrderTraversal(tree -> right);
}

int main() {
    node * root = createNewNode(10);
    root->left = createNewNode(11);
    root->left->left = createNewNode(7);
    root->right = createNewNode(9);
    root->right->left = createNewNode(15);
    root->right->right = createNewNode(8);


    inOrderTraversal(root);
    queue * q = createNewQueue();
    insertIntoTree(root, q, 12);
    printf("\n");
    inOrderTraversal(root);
}
