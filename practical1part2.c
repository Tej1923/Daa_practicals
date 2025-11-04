#include <stdbool.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float *generatedata(int min, int max, int count){
    static float arr[1000000];
    srand(time(NULL)); 
    
    for(int i = 0; i < count; i++){
        float rd_num = min + ((float)rand() / RAND_MAX) * (max - min);
        arr[i] = rd_num;
    }
    return arr;
}

float min_naive_pairwise_comparison (float *arr, int count) {
    for (int i = 0; i < count; i++) {
        bool isMin = true;
        for (int j = 0; j < count; j++) {
            if (i != j && arr[i] > arr[j]) {
                isMin = false;
                break;
            }
        }
        if (isMin) {
            return arr[i]; 
        }
    }
    return -1.0f; 
}

float max_naive_pairwise_comparison(float *arr, int count){
    for (int i = 0; i < count; i++) {
        bool isMax = true;
        for (int j = 0; j < count; j++) {
            if (i != j && arr[i] < arr[j]) {
                isMax = false;
                break;
            }
        }
        if (isMax) {
            return arr[i]; 
        }
    }
    return -1.0f; 
}

int main(){
    int min = -20, max = 50, count = 10000; 
    float *array;
    
    array = generatedata(min, max, count);

    clock_t start, end;
    double cpu_time_used;
    
    printf("--- Task B: Naive Pairwise Comparison (O(n^2)) ---\n");
    printf("Data Count: %d\n", count);
    printf("Range: [%d, %d]\n\n", min, max);

    start = clock();
    float minVal = min_naive_pairwise_comparison(array, count);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Min: %f\n", minVal);
    printf("Time taken to search min: %f sec\n", cpu_time_used);

    start = clock();
    float maxVal = max_naive_pairwise_comparison(array, count);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Max: %f\n", maxVal);
    printf("Time taken to search max: %f sec\n", cpu_time_used);
    
    return 0;
}
