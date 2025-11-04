#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestCommonSubsequence(char* text1, char* text2) {
    int m = strlen(text1);
    int n = strlen(text2);

    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    if (dp == NULL) return 0;

    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)calloc(n + 1, sizeof(int)); 
        if (dp[i] == NULL) {
            for (int k = 0; k < i; k++) free(dp[k]);
            free(dp);
            return 0; 
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    int result = dp[m][n];

    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}