#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    const int *boxA = *(const int **)a;
    const int *boxB = *(const int **)b;

    return boxB[1] - boxA[1];
}

int maximumUnits(int** boxTypes, int boxTypesSize, int boxTypesColSize, int truckSize) {
    qsort(boxTypes, boxTypesSize, sizeof(int*), compare);

    int totalUnits = 0;
    int remaining = truckSize; 

    for (int i = 0; i < boxTypesSize && remaining > 0; i++) {
        int boxCount = boxTypes[i][0];
        int unitsPerBox = boxTypes[i][1];

        if (remaining >= boxCount) {
            totalUnits += boxCount * unitsPerBox;
            remaining -= boxCount;
        } 

        else {
            totalUnits += remaining * unitsPerBox;
            remaining = 0;
        }
    }
    return totalUnits;
}

int main() {
    printf("--- Maximum Units on a Truck (Greedy) ---\n");

    int box_data[4][2] = {
        {5, 10},
        {2, 5},  
        {4, 7},  
        {3, 9}   
    };
    int truckSize = 10;
    int boxTypesSize = 4;
    int boxTypesColSize = 2;

    int* boxTypes[boxTypesSize];
    for(int i = 0; i < boxTypesSize; i++) {
        boxTypes[i] = box_data[i];
    }
    
    printf("Initial Box Types: [[5, 10], [2, 5], [4, 7], [3, 9]]\n");
    printf("Truck Capacity: %d boxes\n", truckSize);

    int max_units = maximumUnits(boxTypes, boxTypesSize, boxTypesColSize, truckSize);

    printf("\nMaximum Total Units Loaded: %d\n", max_units);

    printf("\n--- Test Case 1 ---\n");
    int box_data_2[3][2] = {
        {1, 3},
        {2, 2},
        {3, 1}
    };
    int truckSize_2 = 4;
    int boxTypesSize_2 = 3;
    
    int* boxTypes_2[boxTypesSize_2];
    for(int i = 0; i < boxTypesSize_2; i++) {
        boxTypes_2[i] = box_data_2[i];
    }
    printf("Initial Box Types: [[1, 3], [2, 2], [3, 1]]\n");
    printf("Truck Capacity: %d boxes\n", truckSize_2);
    
    max_units = maximumUnits(boxTypes_2, boxTypesSize_2, boxTypesColSize, truckSize_2);
    printf("\nMaximum Total Units Loaded: %d\n", max_units);

    return 0;
}
