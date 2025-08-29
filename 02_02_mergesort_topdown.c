#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

typedef struct {
    int left;
    int right;
    int stage; // 0 = divide, 1 = merge
} StackFrame;

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // Copy data
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge temporary arrays back into arr
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    // Copy remaining elements
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    // Free memory
    free(L);
    free(R);
}

void mergeSortIterative(int arr[], int n) {
    StackFrame stack[MAX_SIZE];
    int top = -1;

    // Push initial frame (entire array, stage 0 = divide)
    stack[++top] = (StackFrame){0, n - 1, 0};

    // Stack to track merge order separately
    StackFrame mergeStack[MAX_SIZE];
    int mergeTop = -1;

    // Divide Phase
    while (top >= 0) {
        StackFrame current = stack[top--];

        int left = current.left;
        int right = current.right;

        if (left < right) {
            int mid = (left + right) / 2;

            // Push merge task onto mergeStack (to process later)
            mergeStack[++mergeTop] = (StackFrame){left, right, 1};

            // Push right and left halves to divide
            stack[++top] = (StackFrame){mid + 1, right, 0};
            stack[++top] = (StackFrame){left, mid, 0};
        }
    }

    // Merge Phase
    while (mergeTop >= 0) {
        StackFrame current = mergeStack[mergeTop--];
        int left = current.left;
        int right = current.right;
        int mid = (left + right) / 2;

        merge(arr, left, mid, right);
    }
}

// Helper function to print array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Test the iterative merge sort
int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    mergeSortIterative(arr, n);

    printf("Sorted array:\n");
    printArray(arr, n);

    return 0;
}
