#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float *generatedata (float min, float max, float count){
    static float arr[1000000];

    srand(time(NULL)); 
    
    for(int i = 0; i < (int)count; i++){
        float rd_num = min + ((float)rand() / RAND_MAX) * (max - min);
        arr[i] = rd_num;
    }

    return arr;
}

float minlinearsearch (float *arr, int count) {
    float minVal = arr[0];
    
    for(int i = 1; i < count; i++){
        if(minVal > arr[i]){
            minVal = arr[i];
        }
    }
    return minVal;
}

float maxlinearsearch (float *arr, int count) {
    float maxVal = arr[0];
    
    for(int i = 1; i < count; i++){
        if(maxVal < arr[i]){
            maxVal = arr[i];
        }
    }
    return maxVal;
}

void main() {
    float *array;
    int min = 10, max = 90, count = 10000;

    array = generatedata((float)min, (float)max, (float)count);
    
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    float minVal = minlinearsearch(array, count);
    end = clock();
    
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    
    printf("--- Task A: Linear Search (O(n)) ---\n");
    printf("Data Count: %d\n", count);
    printf("Min Value: %f\n", minVal);
    printf("Time to calculate min value: %lf ms\n\n", cpu_time_used);

    min = 100, max = 900, count = 10000;
    array = generatedata((float)min, (float)max, (float)count);
    
    start = clock();
    float maxVal = maxlinearsearch(array, count);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    printf("Min Range: %d, Max Range: %d\n", min, max);
    printf("Max Value: %f\n", maxVal);
    printf("Time to calculate max value: %lf ms\n", cpu_time_used);
}