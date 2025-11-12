#include <stdio.h>
#include <stdbool.h>

#define MAX 20  // maximum vertices (adjustable)

// Function to check if a given set of vertices form a clique
bool isClique(int graph[MAX][MAX], int n, int vertices[], int m) {
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            if (graph[vertices[i]][vertices[j]] == 0)
                return false;
        }
    }
    return true;
}

// Generate all combinations of m vertices
bool hasClique(int graph[MAX][MAX], int n, int m) {
    int vertices[m];
    int i;

    // Initialize first combination
    for (i = 0; i < m; i++)
        vertices[i] = i;

    while (1) {
        // Check if this combination forms a clique
        if (isClique(graph, n, vertices, m))
            return true;

        // Generate next combination (like itertools.combinations)
        i = m - 1;
        while (i >= 0 && vertices[i] == n - m + i)
            i--;

        if (i < 0)
            break;

        vertices[i]++;

        for (int j = i + 1; j < m; j++)
            vertices[j] = vertices[j - 1] + 1;
    }
    return false;
}

// Main function
int main() {
    int n, e, m;
    int graph[MAX][MAX] = {0};
    int u, v;

    printf("Enter number of vertices (n): ");
    scanf("%d", &n);

    printf("Enter number of edges (e): ");
    scanf("%d", &e);

    printf("Enter clique size (m): ");
    scanf("%d", &m);

    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1; // undirected graph
    }

    if (hasClique(graph, n, m))
        printf("The graph contains a clique of size %d.\n", m);
    else
        printf("The graph does NOT contain a clique of size %d.\n", m);

    return 0;
}
