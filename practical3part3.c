#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int start_time;
    int finish_time;
    char Activity_Name[5]; 
    int profit;
} jobs;

int compareMyStructs(const void *a, const void *b) {
    const jobs *job_a = (const jobs *)a;
    const jobs *job_b = (const jobs *)b;
    return job_a->finish_time - job_b->finish_time;
}

int main() {
    jobs j[] = {
        {1, 4, "A1", 10},
        {3, 5, "A2", 15},
        {0, 6, "A3", 14},
        {5, 7, "A4", 12},
        {3, 9, "A5", 20},
        {5, 9, "A6", 30},
        {6, 10, "A7", 32},
        {8, 11, "A8", 28},
        {8, 12, "A9", 30},
        {2, 14, "A10", 40},
        {12, 16, "A11", 45}
    };

    int num_structs = sizeof(j) / sizeof(j[0]);
    printf("--- Activity Selection Problem (Greedy) ---\n");
    printf("Total activities: %d\n", num_structs);

    qsort(j, num_structs, sizeof(jobs), compareMyStructs);

    jobs selected_jobs[11];
    int k = 0; 

    selected_jobs[k] = j[0];
    int total_profit = j[0].profit;
    int last_finish_time = j[0].finish_time;

    for (int i = 1; i < num_structs; i++) {
        if (j[i].start_time >= last_finish_time) {
            k++;
            selected_jobs[k] = j[i];
            total_profit += j[i].profit;
            last_finish_time = j[i].finish_time;
        }
    }
    
    printf("\nSelected Activities (Maximum Compatibility):\n");
    for (int i = 0; i <= k; i++) {
        printf("%s (Start=%d, Finish=%d, Profit=%d)\n",
            selected_jobs[i].Activity_Name,
            selected_jobs[i].start_time,
            selected_jobs[i].finish_time,
            selected_jobs[i].profit);
    }

    printf("\nTotal Profit from Selected Activities: %d\n", total_profit);

    return 0;
}
