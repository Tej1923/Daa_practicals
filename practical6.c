#include <stdio.h>
#include <float.h> 
#include <math.h>  

#define MAX_KEYS 20 

float p[MAX_KEYS];
float q[MAX_KEYS + 1];

float cost[MAX_KEYS + 1][MAX_KEYS + 1]; 
float weight[MAX_KEYS + 1][MAX_KEYS + 1]; 
int root[MAX_KEYS + 1][MAX_KEYS + 1]; 

float optimal_bst(int n) {
    int i, j, k, len;
    float temp_cost;

    for (i = 1; i <= n + 1; i++) {
        cost[i][i - 1] = 0.0;
        weight[i][i - 1] = q[i - 1];
    }

    for (len = 1; len <= n; len++) {
        for (i = 1; i <= n - len + 1; i++) {
            j = i + len - 1; 
            weight[i][j] = weight[i][j - 1] + p[j - 1] + q[j];

            cost[i][j] = FLT_MAX;
            for (k = i; k <= j; k++) {
                temp_cost = cost[i][k - 1] + cost[k + 1][j] + weight[i][j];

                if (temp_cost < cost[i][j]) {
                    cost[i][j] = temp_cost;
                    root[i][j] = k;
                }
            }
        }
    }

    return cost[1][n];
}

int main() {
    int n, i;
    float min_cost;

    printf("Enter the number of book IDs (n): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_KEYS) {
        printf("Invalid input for n.\n");
        return 1;
    }

    printf("Enter the sorted book IDs (keys) - separated by space:\n");
    for (i = 0; i < n; i++) {
        int key;
        scanf("%d", &key); // Read and discard, only needed for tree printing
    }

    printf("Enter the successful search probabilities (p[i]) - %d values:\n", n);
    for (i = 0; i < n; i++) {
        if (scanf("%f", &p[i]) != 1) {
            printf("Invalid input for p[%d].\n", i);
            return 1;
        }
    }

    printf("Enter the unsuccessful search probabilities (q[i]) - %d values:\n", n + 1);
    for (i = 0; i <= n; i++) {
        if (scanf("%f", &q[i]) != 1) {
            printf("Invalid input for q[%d].\n", i);
            return 1;
        }
    }

    min_cost = optimal_bst(n);

    printf("\n--- Results ---\n");
    printf("Minimum Expected Cost of OBST: %.4f\n", min_cost);

    return 0;
}
