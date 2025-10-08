#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// Use a reasonable upper bound for vertices
#define MAX_VERTICES 1000
#define INF INT_MAX

typedef struct {
    int source;
    int destination;
    int weight;
} Edge;

void bellmanFord(Edge edgesList[], int vertices, int edges, int source)
{
    int distance[MAX_VERTICES];
    for (int i = 0; i < vertices; ++i)
        distance[i] = INF;
    distance[source] = 0;

    // Relax edges |V|-1 times
    for (int i = 0; i < vertices - 1; ++i) {
        for (int j = 0; j < edges; ++j) {
            int u = edgesList[j].source;
            int v = edgesList[j].destination;
            int w = edgesList[j].weight;
            if (u < 0 || v < 0 || u >= vertices || v >= vertices)
                continue;
            if (distance[u] == INF)
                continue;
            // use long long to avoid overflow when adding
            long long alt = (long long)distance[u] + (long long)w;
            if (alt < distance[v])
                distance[v] = (int)alt;
        }
    }

    // Check for negative-weight cycles
    for (int i = 0; i < edges; ++i) {
        int u = edgesList[i].source;
        int v = edgesList[i].destination;
        int w = edgesList[i].weight;
        if (u < 0 || v < 0 || u >= vertices || v >= vertices)
            continue;
        if (distance[u] == INF)
            continue;
        long long alt = (long long)distance[u] + (long long)w;
        if (alt < distance[v]) {
            printf("Negative cycle detected\n");
            return;
        }
    }

    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < vertices; ++i) {
        if (distance[i] == INF)
            printf("%d \t\t %s\n", i, "INF");
        else
            printf("%d \t\t %d\n", i, distance[i]);
    }
}
int main(){
    int vertices = 6;

    Edge graph[] = { { 0, 1, 5 }, { 0, 2, 7 }, { 1, 2, 3 },
                     { 1, 3, 4 }, { 1, 4, 6 }, { 3, 4, -1 },
                     { 3, 5, 2 }, { 4, 5, -3 } };
    int edges = sizeof(graph) / sizeof(graph[0]);

    bellmanFord(graph, vertices, edges, 0);
    return 0;
}
