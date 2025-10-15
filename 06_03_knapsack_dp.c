#include <stdio.h>

// Function to solve the 0/1 Knapsack Problem using Dynamic Programming
int knapsack_01(int weights[], int values[], int n, int capacity) {
    int dp[n + 1][capacity + 1];

    // Initialize DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i - 1] <= w)
                dp[i][w] = (values[i - 1] + dp[i - 1][w - weights[i - 1]] > dp[i - 1][w])
                           ? (values[i - 1] + dp[i - 1][w - weights[i - 1]])
                           : dp[i - 1][w];
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    return dp[n][capacity];
}

int main() {
    int weights[] = {2, 3, 4, 5};
    int values[] = {3, 4, 5, 6};
    int capacity = 5;
    int n = sizeof(weights) / sizeof(weights[0]);

    int max_value = knapsack_01(weights, values, n, capacity);
    printf("Maximum value in knapsack: %d\n", max_value);

    return 0;
}
