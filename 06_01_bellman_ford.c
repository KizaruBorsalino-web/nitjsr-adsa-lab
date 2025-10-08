#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 1000
#define INF INT_MAX
typedef struct {
    int source;
    int destination;
    int weight;
} Edge;
void bellmanFord(int graph[MAX_VERTICES][MAX_VERTICES],
                 int vertices, int edges, int source)
{
    int distance[MAX_VERTICES];
     for (int i = 0; i < vertices; ++i)
        distance[i] = INF;
    distance[source] = 0;
    for (int i = 0; i < vertices - 1; ++i) {
        for (int j = 0; j < edges; ++j) {
            if (graph[j][0] != -1
                && distance[graph[j][0]] != INF
                && distance[graph[j][1]]
                       > distance[graph[j][0]]
                             + graph[j][2])
                distance[graph[j][1]]
                    = distance[graph[j][0]] + graph[j][2];
        }
    }
    for (int i = 0; i < edges; ++i) {
        if (graph[i][0] != -1
            && distance[graph[i][0]] != INF
            && distance[graph[i][1]]
                   > distance[graph[i][0]] + graph[i][2]) {
            printf("Negative cycle detected\n");
            return;
        }
    }
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < vertices; ++i)
        printf("%d \t\t %d\n", i, distance[i]);
}
int main()
{
    int vertices = 6;
    int edges = 8;

    int graph[MAX_VERTICES][MAX_VERTICES]
        = { { 0, 1, 5 }, { 0, 2, 7 }, { 1, 2, 3 },
            { 1, 3, 4 }, { 1, 4, 6 }, { 3, 4, -1 },
            { 3, 5, 2 }, { 4, 5, -3 } };
   bellmanFord(graph, vertices, edges, 0);
    return 0;
}
