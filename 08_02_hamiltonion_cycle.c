#include <stdio.h>
#include <stdbool.h>

#define MAX 20  // Maximum number of vertices (can increase as needed)

// Function to check if vertex v can be added at position pos in the Hamiltonian Cycle
bool isSafe(int v, int graph[MAX][MAX], int path[], int pos) {
    // Check if this vertex is adjacent to the previous vertex
    if (graph[path[pos - 1]][v] == 0)
        return false;

    // Check if vertex v is already in the path
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

// Recursive utility function to solve the Hamiltonian Cycle problem
bool hamiltonianCycleUtil(int graph[MAX][MAX], int path[], int pos, int n) {
    // Base case: if all vertices are included in the path
    if (pos == n) {
        // And if the last vertex connects back to the first vertex
        if (graph[path[pos - 1]][path[0]] == 1)
            return true;
        else
            return false;
    }

    // Try different vertices as next candidate
    for (int v = 1; v < n; v++) {
        if (isSafe(v, graph, path, pos)) {
            path[pos] = v;

            if (hamiltonianCycleUtil(graph, path, pos + 1, n))
                return true;

            // Backtrack
            path[pos] = -1;
        }
    }
    return false;
}

// Main Hamiltonian Cycle function
bool hamiltonianCycle(int graph[MAX][MAX], int n) {
    int path[MAX];
    for (int i = 0; i < n; i++)
        path[i] = -1;

    // Start at vertex 0
    path[0] = 0;

    if (!hamiltonianCycleUtil(graph, path, 1, n)) {
        printf("No Hamiltonian Cycle exists.\n");
        return false;
    }

    printf("Hamiltonian Cycle exists:\n");
    for (int i = 0; i < n; i++)
        printf("%d -> ", path[i]);
    printf("%d\n", path[0]); // to show the cycle returning to start

    return true;
}

// Main function
int main() {
    int n, e;
    int graph[MAX][MAX] = {0};
    int u, v;

    printf("Enter number of vertices (n): ");
    scanf("%d", &n);

    printf("Enter number of edges (e): ");
    scanf("%d", &e);

    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1; // undirected graph
    }

    hamiltonianCycle(graph, n);

    return 0;
}
