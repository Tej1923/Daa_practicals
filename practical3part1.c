#include <stdio.h>
#include <stdlib.h>

// Define maximum number of items
#define N 50

// Function to safely swap two integers using pointers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to swap two floats (used for the ratio array)
void swap_float(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

// 1. Greedy approach based on Minimum Weight (Ascending Order)
int minWeightMethod(int weight[], int profit[], int n, int capacity) {
    // Local arrays to hold copies of weights and profits for sorting
    int w[N], p[N];
    for (int i = 0; i < n; i++) {
        w[i] = weight[i];
        p[i] = profit[i];
    }

    // Sort items by weight in ascending order (Bubble Sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (w[j] > w[j + 1]) {
                // Swap both weight and profit together
                swap(&w[j], &w[j + 1]);
                swap(&p[j], &p[j + 1]);
            }
        }
    }

    // Greedy selection
    int totalProfit = 0, totalWeight = 0;
    for (int i = 0; i < n; i++) {
        // If the item can be added fully without exceeding capacity
        if (totalWeight + w[i] < capacity) {
            totalWeight += w[i];
            totalProfit += p[i];
        }
    }
    return totalProfit;
}

// 2. Greedy approach based on Maximum Profit (Descending Order)
int maxProfitMethod(int weight[], int profit[], int n, int capacity) {
    // Local arrays to hold copies
    int w[N], p[N];
    for (int i = 0; i < n; i++) {
        w[i] = weight[i];
        p[i] = profit[i];
    }

    // Sort items by profit in descending order (Bubble Sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j] < p[j + 1]) { // Note the '<' for descending profit
                // Swap both weight and profit together
                swap(&w[j], &w[j + 1]);
                swap(&p[j], &p[j + 1]);
            }
        }
    }

    // Greedy selection
    int totalProfit = 0, totalWeight = 0;
    for (int i = 0; i < n; i++) {
        // If the item can be added fully without exceeding capacity
        if (totalWeight + w[i] < capacity) {
            totalWeight += w[i];
            totalProfit += p[i];
        }
    }
    return totalProfit;
}

// 3. Optimal Greedy approach based on Profit/Weight Ratio (Descending Order)
int ratioMethod(int weight[], int profit[], int n, int capacity) {
    // Local arrays and ratio array
    int w[N], p[N];
    float ratio[N];

    for (int i = 0; i < n; i++) {
        w[i] = weight[i];
        p[i] = profit[i];
        if (w[i] != 0) {
            // Calculate ratio (Profit / Weight)
            ratio[i] = (float)p[i] / w[i];
        } else {
            // Assign a high ratio for items with 0 weight to ensure they are taken
            ratio[i] = (p[i] > 0) ? 1.0e+9 : 0.0; 
        }
    }

    // Sort items by ratio in descending order (Bubble Sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (ratio[j] < ratio[j + 1]) { // Note the '<' for descending ratio
                // Swap ratio
                swap_float(&ratio[j], &ratio[j + 1]);
                // Swap weight and profit (must stay linked)
                swap(&w[j], &w[j + 1]);
                swap(&p[j], &p[j + 1]);
            }
        }
    }

    // Greedy selection
    int totalProfit = 0, totalWeight = 0;
    for (int i = 0; i < n; i++) {
        // If the item can be added fully without exceeding capacity
        if (totalWeight + w[i] < capacity) {
            totalWeight += w[i];
            totalProfit += p[i];
        }
    }
    return totalProfit;
}

int main() {
    int capacity = 850;
    // Data exactly as provided in the source document
    int weight[N] = {7,0,30,22,80,94,11,81,70,64,59,18,0,36,3,8,15,42,9,0,
                     42,47,52,32,26,48,55,6,29,84,2,4,18,56,7,29,93,44,71,
                     3,86,66,31,65,0,79,20,65,52,13};

    int profit [N] = {360,83,59,130,431,67,230,52,93,125,670,892,600,38,48,
                      147,78,256,63,17,120,164,432,35,92,110,22,42,50,323,
                      514,28,87,73,78,15,26,78,210,36,85,189,274,43,33,10,
                      19,389,276,312};

    int n = 50;

    int profit1 = minWeightMethod(weight, profit, n, capacity);
    int profit2 = maxProfitMethod(weight, profit, n, capacity);
    int profit3 = ratioMethod(weight, profit, n, capacity);

    printf("--- Knapsack Problem using Greedy Algorithms ---\n");
    printf("Knapsack Capacity: %d\n\n", capacity);
    
    printf("Total profit by Minimum Weight Method:          %d\n", profit1);
    printf("Total profit by Maximum Profit Method:          %d\n", profit2);
    printf("Total profit by Profit/Weight Ratio Method:     %d\n", profit3);
    printf("\n");

    if (profit1 > profit2 && profit1 > profit3)
        printf("Best method: Minimum Weight\n");
    else if (profit2 > profit1 && profit2 > profit3)
        printf("Best method: Maximum Profit\n");
    else
        printf("Best method: Profit/Weight Ratio\n");

    return 0;
}