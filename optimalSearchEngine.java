class Solution {
    static int optimalSearchTree(int keys[], int freq[], int n) {
    if (n == 0) {
            return 0;
        }

        int[][] cost = new int[n][n];

        for (int i = 0; i < n; i++) {
            cost[i][i] = freq[i];
        }

        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1; 
                cost[i][j] = Integer.MAX_VALUE;

                int sum_freq = 0;
                for (int k = i; k <= j; k++) {
                    sum_freq += freq[k];
                }

                for (int r = i; r <= j; r++) {
                    
                    int left_cost = (r == i) ? 0 : cost[i][r - 1];
                    
                    int right_cost = (r == j) ? 0 : cost[r + 1][j];

                    int current_cost = left_cost + right_cost + sum_freq;

                    if (current_cost < cost[i][j]) {
                        cost[i][j] = current_cost;
                    }
                }
            }
        }

        return cost[0][n - 1];
    }
}