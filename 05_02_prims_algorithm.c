#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 5   // Number of vertices in the graph

// Function to find the vertex with minimum key value
int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the constructed MST
void printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

// Function to construct MST using Prim’s algorithm
void primMST(int graph[V][V]) {
    int parent[V];   // Stores constructed MST
    int key[V];      // Key values used to pick minimum weight edge
    bool mstSet[V];  // True if vertex is included in MST

    // Initialize all keys as infinite
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    // Start from first vertex
    key[0] = 0;       // Make key 0 so that this vertex is picked first
    parent[0] = -1;   // First node is root of MST

    // The MST will have V-1 edges
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum key vertex not yet included in MST
        int u = minKey(key, mstSet);
        mstSet[u] = true;

        // Update key value and parent index of adjacent vertices
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print MST
    printMST(parent, graph);
}

int main() {
    // Example graph (adjacency matrix)
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    printf("Minimum Spanning Tree using Prim’s Algorithm:\n");
    primMST(graph);

    return 0;
}
