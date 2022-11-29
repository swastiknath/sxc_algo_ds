#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXLIMIT 40

/*
 * To Delete a Node From a Binary Tree:
 *      -> Starting from the Root get to the deepest node with Level Order Traversal.
 *      -> Replace it with the data of the node we would like to delete.
 *      -> Delete the reference to the rightmost leaf node by assigning it to NULL.
 */

typedef struct node {
    int value;
    struct node * left;
    struct node * right;
} node;

typedef struct nodeQueue {
    node ** elements;
    int front, rear;
} nodeQueue;


node * createNode (int val){
    node * newNode = malloc(sizeof (node));
    newNode -> left = NULL;
    newNode -> right = NULL;
    newNode -> value = val;
    return newNode;
}

nodeQueue * createQueue() {
    nodeQueue * newQueue = (nodeQueue *) malloc(sizeof(nodeQueue));
    newQueue -> elements = (node **) malloc(MAXLIMIT * sizeof(node *));
    newQueue -> front = -1;
    newQueue -> rear = -1;
    return newQueue;
}

void enQueue(nodeQueue * q, node * n){

    if (q -> rear >= MAXLIMIT - 1){
        printf("\nQueue Overflow.");
        return;
    }
    else {
        if (q-> front == -1) q->front++;
        q -> rear++;
        q -> elements[q -> rear] = n;
    }
}

node * deque (nodeQueue * q){
    if (q -> front == -1 || q -> front > q -> rear ){
        printf("\nQueue Underflow.");
        return NULL;
    } else {
        node * temp = q -> elements[q -> front];
        q -> front++;
        return temp;
    }
}

bool isEmptyQueue(nodeQueue * q){
    if (q -> front == -1 || q -> rear == -1 || q -> front > q -> rear){
        return true;
    }
    return false;
}

void inOrderPrint(node * root){
    if (root == NULL){
        return;
    }
    inOrderPrint(root -> left);
    printf(" %d ", root ->value);
    inOrderPrint(root -> right);
}

node * deleteNode(node * root, int val){
    // Base Cases: 1. If there are nothing in the tree, return null, if the node to be delete matches
    // with the root, delete the root and return null, else if the key to be found is not found in the root, return
    // Root node (Search stops, because there are no other nodes to explore).

    if (root == NULL){
        return NULL;
    }

    if (root -> left == NULL && root -> right == NULL){
        if (root -> value == val) return NULL;
        return root;

    }

    node * foundNode = NULL;
    nodeQueue * q = createQueue();
    node * parentOfCurrentNode;
    node * lastExploredNode;

    enQueue(q, root); // pushing the root node to the queue to reflect the completion of exploration.

    while (!isEmptyQueue(q)){

        lastExploredNode = deque(q);
        if (lastExploredNode ->value == val)
            foundNode = lastExploredNode;

        // Continue Exploring in Level Order Traversal.
        if (lastExploredNode -> left != NULL){
            parentOfCurrentNode = lastExploredNode;
            enQueue(q, lastExploredNode -> left);
        }

        if (lastExploredNode -> right != NULL){
            parentOfCurrentNode = lastExploredNode;
            enQueue(q, lastExploredNode->right);
        }

    }

    if (foundNode != NULL){
        foundNode -> value = lastExploredNode -> value; // Replacing the value of the node to be deleted with the deepest node's values.
        // Disconnecting the links with the last edge.
        if (parentOfCurrentNode -> right == lastExploredNode) parentOfCurrentNode -> right = NULL;
        else {
            parentOfCurrentNode -> left = NULL;
        }

    }
    return root;
}




int main() {
    node * root = createNode(9);
    root->left = createNode(2);
    root->left->left = createNode(4);
    root->left->right = createNode(7);
    root->right = createNode(8);

    inOrderPrint(root);

    deleteNode(root, 7);
    printf("\n");
    inOrderPrint(root);

    return 0;
}
