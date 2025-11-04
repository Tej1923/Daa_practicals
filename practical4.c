#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    long long sum;
    int start;
    int end;
} SubarrayResult;

long long max_ll(long long a, long long b) {
    return (a > b) ? a : b;
}

long long max_three_ll(long long a, long long b, long long c) {
    return max_ll(a, max_ll(b, c));
}

SubarrayResult max_crossing_subarray(const int resources[], int low, int mid, int high, int constraint) {
    SubarrayResult result = {0, -1, -1};
    long long max_sum = 0;

    if (constraint <= 0) {
        result.sum = 0;
        return result;
    }

    long long left_sum = 0;
    long long current_sum = 0;
    int max_left = mid; 

    for (int i = mid; i >= low; i--) {
        current_sum += resources[i];
        
        if (current_sum <= constraint && current_sum > left_sum) {
            left_sum = current_sum;
            max_left = i;
        }
    }
    
    long long right_sum = 0;
    current_sum = 0;
    int max_right = mid; 

    for (int j = mid + 1; j <= high; j++) {
        current_sum += resources[j];
        
        if (current_sum <= constraint && current_sum > right_sum) {
            right_sum = current_sum;
            max_right = j;
        }
    }

    long long combined_sum = left_sum + right_sum;

    if (combined_sum > constraint) {
        if (left_sum >= right_sum) {
            result.sum = left_sum;
            result.start = max_left;
            result.end = mid;
        } else {
            result.sum = right_sum;
            result.start = mid + 1;
            result.end = max_right;
        }
    } else if (combined_sum > max_sum) {
        max_sum = combined_sum;
        result.sum = max_sum;
        result.start = max_left;
        result.end = max_right;
    }

    return result;
}

SubarrayResult max_subarray_sum_dc(const int resources[], int low, int high, int constraint) {
    if (low == high) {
        if (resources[low] <= constraint) {
            return (SubarrayResult){resources[low], low, low};
        } else {
            return (SubarrayResult){0, -1, -1};
        }
    }

    if (low > high) {
        return (SubarrayResult){0, -1, -1};
    }
    
    int mid = (low + high) / 2;

    SubarrayResult left_res = max_subarray_sum_dc(resources, low, mid, constraint);

    SubarrayResult right_res = max_subarray_sum_dc(resources, mid + 1, high, constraint);

    SubarrayResult crossing_res = max_crossing_subarray(resources, low, mid, high, constraint);

    long long max_sum = max_three_ll(left_res.sum, right_res.sum, crossing_res.sum);

    if (max_sum == left_res.sum) {
        return left_res;
    } else if (max_sum == right_res.sum) {
        return right_res;
    } else {
        return crossing_res;
    }
}

void find_max_constrained_subarray(const int resources[], int size, int constraint) {
    printf("Input: resources=[");
    for(int i=0; i<size; i++) {
        printf("%d%s", resources[i], (i == size-1) ? "" : ", ");
    }
    printf("], constraint=%d\n", constraint);

    if (size == 0) {
        printf("Output: No feasible subarray (Empty input array).\n");
        printf("----------------------------------\n");
        return;
    }
    
    if (constraint <= 0) {
        int has_zero = 0;
        for(int i=0; i<size; i++) {
            if (resources[i] == 0) {
                has_zero = 1;
                break;
            }
        }
        if (has_zero) {
            printf("Output: Best subarray: [0] (single element 0) → sum = 0. Start=%d, End=%d\n", -1, -1);
        } else {
             printf("Output: No feasible subarray (Constraint is <= 0 and no element is 0).\n");
        }
        printf("----------------------------------\n");
        return;
    }


    SubarrayResult final_res = max_subarray_sum_dc(resources, 0, size - 1, constraint);

    if (final_res.sum == 0 && final_res.start == -1) {
        printf("Output: No feasible subarray (max sum is 0).\n");
    } else {
        printf("Output: Best subarray: [");
        for(int i=final_res.start; i<=final_res.end; i++) {
            printf("%d%s", resources[i], (i == final_res.end) ? "" : ", ");
        }
        printf("] → sum = %lld. Start Index=%d, End Index=%d\n", 
               final_res.sum, final_res.start, final_res.end);
    }
    printf("----------------------------------\n");
}

int main() {
    int r1[] = {2, 1, 3, 4};
    find_max_constrained_subarray(r1, 4, 5);

    int r2[] = {2, 2, 2, 2};
    find_max_constrained_subarray(r2, 4, 4); 

    int r3[] = {1, 5, 2, 3};
    find_max_constrained_subarray(r3, 4, 5);

    int r4[] = {6, 7, 8};
    find_max_constrained_subarray(r4, 3, 5); 

    int r5[] = {1, 2, 3, 2, 1};
    find_max_constrained_subarray(r5, 5, 5); 

    int r6[] = {1, 1, 1, 1, 1};
    find_max_constrained_subarray(r6, 5, 4);

    int r7[] = {4, 2, 3, 1};
    find_max_constrained_subarray(r7, 4, 5); 

    int r8[] = {};
    find_max_constrained_subarray(r8, 0, 10); 
    int r9[] = {1, 2, 3};
    find_max_constrained_subarray(r9, 3, 0); 

    int r10[] = {1000000000, 1, 2, 3};
    find_max_constrained_subarray(r10, 4, 1000000000);

    return 0;
}