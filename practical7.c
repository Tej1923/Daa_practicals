#include <stdio.h>
#include <stdbool.h>

#define N 5 

int G[N][N] = {
    {0, 1, 1, 0, 1}, 
    {1, 0, 1, 1, 0}, 
    {1, 1, 0, 1, 0},
    {0, 1, 1, 0, 1}, 
    {1, 0, 0, 1, 0}  
};

int path[N];

void printSolution() {
    printf("Hamiltonian Cycle found:\n");

    for (int i = 0; i < N; i++) {
       
        printf("%c -> ", 'A' + path[i]);
    }
   
    printf("%c\n", 'A' + path[0]); 
}

bool isSafe(int v, int pos) {
  
    if (G[path[pos - 1]][v] == 0) {
        return false;
    }

    for (int i = 0; i < pos; i++) {
        if (path[i] == v) {
            return false;
        }
    }

    return true; 
}

bool hamiltonianCycleUtil(int pos) {
 
    if (pos == N) {

        if (G[path[pos - 1]][path[0]] == 1) {
            return true; 
        } else {
            return false; 
        }
    }

    for (int v = 0; v < N; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;

            if (hamiltonianCycleUtil(pos + 1) == true) {
                return true;
            }

        }
    }
    return false;
}

void findHamiltonianCycle() {

    for (int i = 0; i < N; i++) {
        path[i] = -1;
    }

    path[0] = 0; 

    if (hamiltonianCycleUtil(1) == false) {
        printf("\nNo Hamiltonian Cycle exists in the given graph (starting from A).\n");
    } else {
        printSolution();
    }
}

int main() {
    printf("--- Hamiltonian Cycle Implementation (Backtracking) ---\n");
    findHamiltonianCycle();
    return 0;
}