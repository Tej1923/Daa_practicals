#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 10

int minKey(int key[], int mstSet[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void printMST(int parent[], int graph[MAX_VERTICES][MAX_VERTICES], int V) {
    long long total_min_cost = 0;
    printf("\n** Freckle Connections (Minimum Spanning Tree) **\n");
    printf("Edge \t\tDistance\n");
 
    for (int i = 1; i < V; i++) {
        printf("F%d - F%d \t%d\n", parent[i] + 1, i + 1, graph[i][parent[i]]);
        total_min_cost += graph[i][parent[i]];
    }

    printf("\n** Total Minimum Ink Used (Cost) **: %lld\n", total_min_cost);
}

void primMST(int graph[MAX_VERTICES][MAX_VERTICES], int V) {
    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    int mstSet[MAX_VERTICES];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);

        mstSet[u] = 1;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph, V);
}

int main_part_a() {
    int V;
    printf("Enter the number of freckles (max %d): ", MAX_VERTICES);
    if (scanf("%d", &V) != 1 || V < 2 || V > MAX_VERTICES) {
        printf("Invalid number of freckles.\n");
        return 1;
    }

    int graph[MAX_VERTICES][MAX_VERTICES];
    printf("Enter the distance matrix (Freckle i to Freckle j):\n");

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("Distance from F%d to F%d: ", i + 1, j + 1);
            if (scanf("%d", &graph[i][j]) != 1) {
                printf("Invalid input.\n");
                return 1;
            }
 
            if (i == j) graph[i][j] = 0;
            if (graph[i][j] < 0) graph[i][j] = 0;
        }
    }

    primMST(graph, V);
    
    return 0;
}