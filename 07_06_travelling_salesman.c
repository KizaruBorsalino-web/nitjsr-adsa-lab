#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define INF 999999

int n;  // Number of cities
int cost[100][100];
int visited[100];
int min_cost = INF;

// Function to find the minimum tour cost using backtracking
void tsp(int city, int count, int current_cost, int start) {
    if (count == n && cost[city][start]) {
        int total_cost = current_cost + cost[city][start];
        if (total_cost < min_cost)
            min_cost = total_cost;
        return;
    }

    for (int next = 0; next < n; next++) {
        if (!visited[next] && cost[city][next]) {
            visited[next] = 1;
            tsp(next, count + 1, current_cost + cost[city][next], start);
            visited[next] = 0;
        }
    }
}

// Generate a random symmetric cost matrix
void generateGraph(int nodes) {
    n = nodes;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                cost[i][j] = 0;
            else
                cost[i][j] = rand() % 90 + 10;  // Random cost between 10–99
        }
    }
}

// Run TSP and measure execution time
double runTSP(int nodes) {
    generateGraph(nodes);
    for (int i = 0; i < nodes; i++)
        visited[i] = 0;

    min_cost = INF;
    visited[0] = 1;

    clock_t start_time = clock();
    tsp(0, 1, 0, 0);
    clock_t end_time = clock();

    double exec_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    return exec_time;
}

int main() {
    srand(time(0));
    int sizes[] = {10, 20, 40, 60, 100};
    int num_sizes = 5;
    double times[5];

    printf("TSP Execution Time Table\n");
    printf("-------------------------------\n");
    printf("Nodes\tExecution Time (sec)\n");
    printf("-------------------------------\n");

    for (int i = 0; i < num_sizes; i++) {
        if (sizes[i] > 12) {
            printf("%d\tToo large for brute force (>12 nodes)\n", sizes[i]);
            continue;
        }
        double t = runTSP(sizes[i]);
        times[i] = t;
        printf("%d\t%.6f\n", sizes[i], t);
    }

    printf("-------------------------------\n");
    printf("\n*Note: Brute-force TSP becomes infeasible beyond 12 nodes due to factorial growth.\n");
    return 0;
}
