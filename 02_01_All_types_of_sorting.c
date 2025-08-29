// Queston 2A: Implement the (i) insertion sort, (ii) bubble sort, (iii) selection sort, (iv) shell sort, (v) quick sort, (vi)
// merge sort, (vii) heap sort, (viii) radix sort, (ix) counting sort, (x) bucket sort, (xi) radix exchange sort,
// and (xii) address calculation sort.    


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

// (i) Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key)
            arr[j + 1] = arr[j--];
        arr[j + 1] = key;
    }
}

// (ii) Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1]) {
                int t = arr[j]; arr[j] = arr[j+1]; arr[j+1] = t;
            }
}

// (iii) Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++)
            if (arr[j] < arr[min]) min = j;
        int t = arr[i]; arr[i] = arr[min]; arr[min] = t;
    }
}

// (iv) Shell Sort
void shellSort(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2)
        for (int i = gap; i < n; i++) {
            int temp = arr[i], j;
            for (j = i; j >= gap && arr[j-gap] > temp; j -= gap)
                arr[j] = arr[j-gap];
            arr[j] = temp;
        }
}

// (v) Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high], i = low-1;
        for (int j = low; j < high; j++)
            if (arr[j] < pivot) {
                i++;
                int t = arr[i]; arr[i] = arr[j]; arr[j] = t;
            }
        int t = arr[i+1]; arr[i+1] = arr[high]; arr[high] = t;
        int pi = i+1;
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

// (vi) Merge Sort
void merge(int arr[], int l, int m, int r) {
    int n1 = m-l+1, n2 = r-m;
    int *L = malloc(n1*sizeof(int)), *R = malloc(n2*sizeof(int));
    for (int i = 0; i < n1; i++) L[i] = arr[l+i];
    for (int j = 0; j < n2; j++) R[j] = arr[m+1+j];
    int i=0, j=0, k=l;
    while (i<n1 && j<n2) arr[k++] = (L[i]<R[j]) ? L[i++] : R[j++];
    while (i<n1) arr[k++] = L[i++];
    while (j<n2) arr[k++] = R[j++];
    free(L); free(R);
}
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

// (vii) Heap Sort
void heapify(int arr[], int n, int i) {
    int largest = i, l = 2*i+1, r = 2*i+2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        int t = arr[i]; arr[i] = arr[largest]; arr[largest] = t;
        heapify(arr, n, largest);
    }
}
void heapSort(int arr[], int n) {
    for (int i = n/2-1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n-1; i > 0; i--) {
        int t = arr[0]; arr[0] = arr[i]; arr[i] = t;
        heapify(arr, i, 0);
    }
}

// (viii) Radix Sort (LSD, base 10)
int getMax(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > mx) mx = arr[i];
    return mx;
}
void countSortRadix(int arr[], int n, int exp) {
    int *output = malloc(n*sizeof(int)), count[10] = {0};
    for (int i = 0; i < n; i++) count[(arr[i]/exp)%10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i-1];
    for (int i = n-1; i >= 0; i--) {
        output[count[(arr[i]/exp)%10]-1] = arr[i];
        count[(arr[i]/exp)%10]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
    free(output);
}
void radixSort(int arr[], int n) {
    int m = getMax(arr, n);
    for (int exp = 1; m/exp > 0; exp *= 10)
        countSortRadix(arr, n, exp);
}

// (ix) Counting Sort (non-negative integers)
void countingSort(int arr[], int n) {
    int max = arr[0], min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }
    int range = max - min + 1;
    int *count = calloc(range, sizeof(int));
    for (int i = 0; i < n; i++) count[arr[i] - min]++;
    int idx = 0;
    for (int i = 0; i < range; i++)
        while (count[i]--) arr[idx++] = i + min;
    free(count);
}

// (x) Bucket Sort (for [0,1) floats, can be adapted for integers)
void bucketSort(float arr[], int n) {
    int i, j, k;
    int bucketNum = n;
    float **buckets = malloc(bucketNum * sizeof(float*));
    int *bucketSizes = calloc(bucketNum, sizeof(int));
    for (i = 0; i < bucketNum; i++)
        buckets[i] = malloc(n * sizeof(float));
    for (i = 0; i < n; i++) {
        int idx = arr[i] * bucketNum;
        buckets[idx][bucketSizes[idx]++] = arr[i];
    }
    for (i = 0; i < bucketNum; i++)
        insertionSort((int*)buckets[i], bucketSizes[i]);
    k = 0;
    for (i = 0; i < bucketNum; i++)
        for (j = 0; j < bucketSizes[i]; j++)
            arr[k++] = buckets[i][j];
    for (i = 0; i < bucketNum; i++) free(buckets[i]);
    free(buckets); free(bucketSizes);
}

// (xi) Radix Exchange Sort (MSD radix sort, binary)
void radixExchangeSort(int arr[], int left, int right, int bit) {
    if (left >= right || bit < 0) return;
    int i = left, j = right;
    while (i <= j) {
        while (i <= j && !(arr[i] & (1 << bit))) i++;
        while (i <= j && (arr[j] & (1 << bit))) j--;
        if (i < j) {
            int t = arr[i]; arr[i] = arr[j]; arr[j] = t;
            i++; j--;
        }
    }
    radixExchangeSort(arr, left, j, bit-1);
    radixExchangeSort(arr, i, right, bit-1);
}

// (xii) Address Calculation Sort (Hash sort, for demonstration)
void addressCalculationSort(int arr[], int n) {
    int *output = malloc(n * sizeof(int));
    int max = arr[0], min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }
    for (int i = 0; i < n; i++) {
        int idx = (int)((double)(arr[i] - min) / (max - min + 1) * n);
        while (output[idx] != 0) idx = (idx + 1) % n;
        output[idx] = arr[i];
    }
    int j = 0;
    for (int i = 0; i < n; i++)
        if (output[i] != 0) arr[j++] = output[i];
    free(output);
}

