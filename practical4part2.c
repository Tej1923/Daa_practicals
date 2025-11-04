int max(int a, int b) {
    return (a > b) ? a : b;
}

int maxSubArray(int* nums, int numsSize) {
    if (numsSize == 0) {
        return 0;
    }
    int max_so_far = nums[0];
    int current_max = nums[0];
    for (int i = 1; i < numsSize; i++) {
        current_max = max(nums[i], current_max + nums[i]);
        max_so_far = max(max_so_far, current_max);
    }
    return max_so_far;
}