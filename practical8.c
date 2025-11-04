#include <stdio.h>
#include <stdbool.h>

#define V 10 
int m;

int G[V][V]; 
int color[V];
int n;


bool isSafe(int v, int c) {
    for (int i = 0; i < n; i++) {
        if (G[v][i] == 1 && color[i] == c) {
            return false; 
    }
}
return true;
}

bool graphColoringUtil(int k) {
    if (k == n) {
        printf("Solution Found with %d colors:\n", m);
        for (int i = 0; i < n; i++) {
            printf("Vertex %d: Color %d\n", i, color[i]);
        }
        return true;
    }

    for (int c = 1; c <= m; c++) {
        if (isSafe(k, c)) {
            color[k] = c;
            if (graphColoringUtil(k + 1) == true) {
                return true;
            }
            color[k] = 0; 
        }
    }
    return false;
}
    void graphColoring() {
    int i, j;
    printf("Enter the number of nodes (V): ");
    scanf("%d", &n);

    printf("Enter the Adjacency Matrix (%dx%d):\n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &G[i][j]);
        }
    }

    for (i = 0; i < n; i++) {
        color[i] = 0;
    }
    
    printf("Enter the maximum number of colors (m) to use: ");
    scanf("%d", &m);

    printf("\nAttempting to color the graph with m = %d colors.\n", m);
    if (graphColoringUtil(0) == false) {
        printf("Solution does not exist with %d colors.\n", m);
    }
}

int main() {
    graphColoring();
    return 0;
}