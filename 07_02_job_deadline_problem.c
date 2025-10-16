#include <stdio.h>
#include <stdlib.h>

// Structure to represent a job
typedef struct {
    char id;      // Job ID (like A, B, C, ...)
    int deadline; // Deadline for the job
    int profit;   // Profit for the job
} Job;

// Comparison function to sort jobs by profit in descending order
int compare(const void *a, const void *b) {
    Job *j1 = (Job *)a;
    Job *j2 = (Job *)b;
    return j2->profit - j1->profit;  // descending order
}

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to find the maximum deadline
int findMaxDeadline(Job jobs[], int n) {
    int maxDeadline = jobs[0].deadline;
    for (int i = 1; i < n; i++) {
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;
    }
    return maxDeadline;
}

// Function to implement Job Sequencing with Deadline
void jobSequencing(Job jobs[], int n) {
    // Sort jobs in decreasing order of profit
    qsort(jobs, n, sizeof(Job), compare);

    int maxDeadline = findMaxDeadline(jobs, n);

    char result[maxDeadline + 1];  // To store job sequence
    int slot[maxDeadline + 1];     // Time slot availability

    for (int i = 0; i <= maxDeadline; i++)
        slot[i] = 0; // Initialize all slots as free

    int totalProfit = 0;

    // Place each job in its suitable time slot
    for (int i = 0; i < n; i++) {
        // Find a free slot for this job (starting from its deadline)
        for (int j = jobs[i].deadline; j > 0; j--) {
            if (slot[j] == 0) {
                slot[j] = 1;  // Mark slot as occupied
                result[j] = jobs[i].id;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    // Display the result
    printf("\nJob sequence: ");
    for (int i = 1; i <= maxDeadline; i++) {
        if (slot[i])
            printf("%c ", result[i]);
    }
    printf("\nTotal Profit: %d\n", totalProfit);
}

// Main function
int main() {
    int n;
    printf("Enter number of jobs: ");
    scanf("%d", &n);

    Job jobs[n];
    printf("Enter Job ID, Deadline, and Profit for each job:\n");
    for (int i = 0; i < n; i++) {
        scanf(" %c %d %d", &jobs[i].id, &jobs[i].deadline, &jobs[i].profit);
    }

    jobSequencing(jobs, n);
    return 0;
}
