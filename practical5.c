#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DIAG 1 
#define UP 2  
#define LEFT 3 

void findLCS(const char *X, const char *Y) {
    int m = strlen(X);
    int n = strlen(Y);

    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    int **path = (int **)malloc((m + 1) * sizeof(int *));

    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
        path[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    for (int i = 0; i <= m; i++) dp[i][0] = 0;
    for (int j = 0; j <= n; j++) dp[0][j] = 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                path[i][j] = DIAG;
            } else {
                if (dp[i - 1][j] >= dp[i][j - 1]) {
                    dp[i][j] = dp[i - 1][j];
                    path[i][j] = UP;
                } else {
                    dp[i][j] = dp[i][j - 1];
                    path[i][j] = LEFT;
                }
            }
        }
    }

    printf("--- Output ---\n\n");
    printf("## 📈 Cost Matrix (DP Table) with Lengths\n");
    printf("   ");
    for (int j = 0; j < n; j++) printf(" %c ", Y[j]);
    printf("\n");

    for (int i = 0; i <= m; i++) {
        if (i == 0) printf(" ");
        else printf("%c", X[i - 1]);
        for (int j = 0; j <= n; j++) {
            printf(" %d ", dp[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int lcs_length = dp[m][n];
    printf("## Length of Longest Common Subsequence: **%d**\n", lcs_length);
    printf("\n");
    char *lcs = (char *)malloc((lcs_length + 1) * sizeof(char));
    lcs[lcs_length] = '\0';

    int i = m;
    int j = n;
    int k = lcs_length - 1;

    while (i > 0 && j > 0) {
        if (path[i][j] == DIAG) {
            lcs[k] = X[i - 1];
            k--;
            i--;
            j--;
        } else if (path[i][j] == UP) {
            i--;
        } else {
            j--;
        }
    }

    printf("## ✨ Longest Common Subsequence (LCS): **%s**\n", lcs);
    printf("\n");
    printf("Direction Matrix (Path Table)\n");
    printf("   ");
    for (int j = 0; j < n; j++) printf(" %c ", Y[j]);
    printf("\n");

    for (int i = 0; i <= m; i++) {
        if (i == 0) printf(" ");
        else printf("%c", X[i - 1]);
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) printf(" - ");
            else {
                if (path[i][j] == DIAG) printf(" \\ "); 
                else if (path[i][j] == UP) printf(" ^ "); 
                else printf(" < "); 
            }
        }
        printf("\n");
    }

    for (int i = 0; i <= m; i++) {
        free(dp[i]);
        free(path[i]);
    }
    free(dp);
    free(path);
    free(lcs);
}

int main() {
    const char *X = "AGCCCTAAGGGCTACCTAGCTT"; 
    const char *Y = "GACAGCCTACAAGCGTTAGCTTG"; 


    findLCS(X, Y);

    return 0;
}