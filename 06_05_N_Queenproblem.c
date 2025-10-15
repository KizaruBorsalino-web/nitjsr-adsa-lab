#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 20  // Maximum board size

int board[MAX_N];
int n;
int solutionCount = 0;

int is_safe(int row, int col) {
    for (int prev_row = 0; prev_row < row; prev_row++) {
        // Check same column or diagonal
        if (board[prev_row] == col || 
            abs(board[prev_row] - col) == abs(prev_row - row)) {
            return 0; // Not safe
        }
    }
    return 1; // Safe
}

void print_solution() {
    solutionCount++;
    printf("Solution %d:\n", solutionCount);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i] == j)
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}

void solve(int row) {
    if (row == n) {
        print_solution();
        return;
    }

    for (int col = 0; col < n; col++) {
        if (is_safe(row, col)) {
            board[row] = col;
            solve(row + 1);
            board[row] = -1;  // Backtrack
        }
    }
}

int main() {
    printf("Enter the value of N: ");
    scanf("%d", &n);

    if (n > MAX_N) {
        printf("N is too large! Please use N <= %d\n", MAX_N);
        return 1;
    }

    // Initialize board
    for (int i = 0; i < n; i++) board[i] = -1;

    solve(0);

    printf("Total solutions for %d-Queens: %d\n", n, solutionCount);

    return 0;
}
