#include <stdio.h>

// Global variable to track the maximum value found
int max_value = 0;

// Recursive backtracking function
void backtrack(int index, int current_weight, int current_value,
               int weights[], int values[], int n, int capacity) {
    // Base case: all items considered
    if (index == n) {
        if (current_value > max_value)
            max_value = current_value;
        return;
    }

    // Exclude current item
    backtrack(index + 1, current_weight, current_value, weights, values, n, capacity);

    // Include current item (if it fits)
    if (current_weight + weights[index] <= capacity) {
        backtrack(index + 1,
                  current_weight + weights[index],
                  current_value + values[index],
                  weights, values, n, capacity);
    }
}

int knapsack_backtracking(int weights[], int values[], int n, int capacity) {
    max_value = 0; // reset global max_value before starting
    backtrack(0, 0, 0, weights, values, n, capacity);
    return max_value;
}

int main() {
    int weights[] = {2, 3, 4, 5};
    int values[] = {3, 4, 5, 6};
    int capacity = 5;
    int n = sizeof(weights) / sizeof(weights[0]);

    int result = knapsack_backtracking(weights, values, n, capacity);
    printf("Maximum value in knapsack (backtracking): %d\n", result);

    return 0;
}
