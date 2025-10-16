#include <stdio.h>

// Function to find the minimum number of coins using the greedy method
void coinChange(int coins[], int n, int amount) {
    int i, count[20] = {0};
    
    printf("Coins used to make change for %d:\n", amount);

    for (i = 0; i < n; i++) {
        if (coins[i] <= amount) {
            count[i] = amount / coins[i];   // number of coins of this denomination
            amount -= count[i] * coins[i];  // reduce remaining amount
        }
    }

    // Display result
    for (i = 0; i < n; i++) {
        if (count[i] != 0)
            printf("Coin %d: %d\n", coins[i], count[i]);
    }

    if (amount > 0)
        printf("Remaining amount that cannot be changed: %d\n", amount);
}

int main() {
    int n, i, amount;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    int coins[n];

    printf("Enter the coin denominations (in descending order):\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }

    printf("Enter the amount to make change for: ");
    scanf("%d", &amount);

    coinChange(coins, n, amount);

    return 0;
}
