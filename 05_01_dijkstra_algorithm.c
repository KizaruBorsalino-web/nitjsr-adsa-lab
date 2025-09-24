#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 6   // Number of vertices in the graph

// Function to find the vertex with the minimum distance value
int minDistance(int dist[], bool visited[]) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the shortest path from source to all vertices
void printSolution(int dist[], int src) {
    printf("Vertex \t Distance from Source %d\n", src);
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Dijkstra’s Algorithm implementation
void dijkstra(int graph[V][V], int src) {
    int dist[V];       // Output array: dist[i] will hold shortest distance from src to i
    bool visited[V];   // visited[i] is true if vertex i is included in shortest path tree

    // Initialize all distances as infinite and visited[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    // Distance from source to itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of unvisited vertices
        int u = minDistance(dist, visited);
        visited[u] = true;

        // Update dist[] of the adjacent vertices
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the constructed distance array
    printSolution(dist, src);
}

int main() {
    // Example graph represented using adjacency matrix
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0},
        {4, 0, 8, 0, 0, 0},
        {0, 8, 0, 7, 0, 4},
        {0, 0, 7, 0, 9, 14},
        {0, 0, 0, 9, 0, 10},
        {0, 0, 4, 14, 10, 0}
    };

    int source = 0;  // Starting node
    dijkstra(graph, source);

    return 0;
}
