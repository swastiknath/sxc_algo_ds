#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXLIM 30

// A Tree is a Full Binary Tree if each node is either a leaf node or have two children.
typedef struct node {
    int value;
    struct node * left;
    struct node * right;
}node;

node * createNewNode(int val){
    node * newNode = (node *) malloc(sizeof (node));
    newNode -> left = NULL;
    newNode -> right = NULL;
    newNode -> value = val;
    return newNode;
}

bool isFullTreeRecursive (node * root){
    if (root == NULL){
        return true; //NULL Tree is Full;
    }
    if (root -> left == NULL && root -> right == NULL){
        // Means this is a leaf node, leaf nodes are Full.
        return true;
    }
    if ((root -> left != NULL) && (root -> right != NULL)) {
        return isFullTreeRecursive(root -> left) && isFullTreeRecursive(root -> right);
    }

    return false; // If none of the above conditions work then it's not a full binary tree as there might be just 1 child in any node.
}


typedef struct nodeQueue {
    node ** elements;
    int front, rear;
} nodeQueue;

nodeQueue * createNewQueue(){
    nodeQueue * q = (nodeQueue *) malloc(sizeof (nodeQueue));
    q -> elements = (node **) malloc(MAXLIM * sizeof (node *));
    q -> front = -1;
    q -> rear = -1;
    return q;
}

void enqueue(nodeQueue * q, node * n){
    if (q -> rear == MAXLIM - 1){
        printf("\nQueue Overflow!");
        return;
    }
    if (q -> front == -1) q->front++;
    q -> rear++;
    q -> elements[q -> rear] = n;
}

node * dequeue (nodeQueue * q){
    if (q -> front > q -> rear || q -> front == -1){
        printf("\n Queue Underflow!");
        return NULL;
    }
    node * tmp = q -> elements[q -> front];
    q -> front++;
    return tmp;
}

bool isEmptyQueue(nodeQueue *q){
    if (q -> front == -1 || q ->front > q -> rear) {
        return true;
    }
    return false;
}

bool isFullTreeIterative (node * root){

    // Create a queue to store nodes
    nodeQueue * q = createNewQueue();
    //Store the root of the tree in the queue
    enqueue(q, root);
    //Traverse until the queue is not empty.
    while (!isEmptyQueue(q)){
        node * currentNode = dequeue(q);
        //If the current node is NULL return false.
        if (currentNode == NULL) return false;
        // If the current node is not a leaf insert root->left and root->right in the queue.
        if ((currentNode -> left != NULL) && (currentNode -> right != NULL)){
            enqueue(q, currentNode -> left);
            enqueue(q, currentNode -> right);
        }

    }
    //If the queue is empty return true.
    return true;
}


int main() {
    node* root = NULL;
    root = createNewNode(10);
    root->left = createNewNode(20);
    root->right = createNewNode(30);

    root->left->right = createNewNode(40);
    root->left->left = createNewNode(50);
    root->right->left = createNewNode(60);
    root->right->right = createNewNode(70);

    root->left->left->left = createNewNode(80);
    root->left->left->right = createNewNode(90);
    root->left->right->left = createNewNode(80);
    root->left->right->right = createNewNode(90);
    root->right->left->left = createNewNode(80);
    root->right->left->right = createNewNode(90);
    root->right->right->left = createNewNode(80);
    root->right->right->right = createNewNode(90);

    if (isFullTreeIterative(root)){
        printf("\nBinary Tree is FULL.");
    }
    return 0;
}
