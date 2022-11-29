#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define V 6

typedef struct pair {
    int a;
    int b;
} pair;

int find (int x, int * parent){
    if (x == parent[x]){
        return x;
    }
    return parent[x] = find(parent[x], parent);
}

pair * createPair(int x, int y){
    pair * newPair = malloc(sizeof (pair));
    newPair ->a = x;
    newPair -> b = y;
    return newPair;
}

pair ** findExtraEdges (int n, int e, pair ** edges, int numEdges){
    pair **answer = malloc(50 * sizeof (pair *));
    int parent [V];
    int i, idx;
    for (i = 0; i < V; i++ ){
        parent[i] = i;
    }

    for (idx = 0; idx < numEdges; idx++){
        int vParent = find(edges[idx]->a, parent);
        int uParent = find(edges[idx]->b, parent);

        if (vParent == uParent){
            pair * p;
            if (edges[idx]-> a < edges[idx]-> b){
                p = createPair(edges[idx] -> a, edges[idx]->b);
            } else {
                p = createPair(edges[idx] -> b, edges[idx]->a);
            }
            answer[idx] = p;
        } else {
            parent[vParent] = uParent;
        }
    }
    return answer;

}



int main() {

    int N = 3;
    int E = 3;
    pair ** edges = {(pair **) createPair(0, 1), createPair(1, 2), createPair(2, 0), createPair(0, 2)};

}
