#include <stdio.h>
#include <stdbool.h>

#define MAX 100  // Maximum number of vertices

// Simple queue implementation for BFS
struct Queue {
    int items[MAX];
    int front, rear;
};

void initQueue(struct Queue *q) {
    q->front = 0;
    q->rear = -1;
}

bool isEmpty(struct Queue *q) {
    return q->front > q->rear;
}

void enqueue(struct Queue *q, int value) {
    q->items[++q->rear] = value;
}

int dequeue(struct Queue *q) {
    return q->items[q->front++];
}

// Function to check if a graph is bipartite
bool isBipartite(int graph[MAX][MAX], int n) {
    int color[MAX];
    for (int i = 0; i < n; i++)
        color[i] = -1;  // -1 means uncolored

    struct Queue q;

    for (int start = 0; start < n; start++) {
        if (color[start] == -1) {  // Unvisited vertex
            initQueue(&q);
            enqueue(&q, start);
            color[start] = 0;  // Start coloring with 0

            while (!isEmpty(&q)) {
                int u = dequeue(&q);

                for (int v = 0; v < n; v++) {
                    if (graph[u][v] == 1) {
                        if (color[v] == -1) {
                            color[v] = 1 - color[u];
                            enqueue(&q, v);
                        } else if (color[v] == color[u]) {
                            return false; // Same color on both ends
                        }
                    }
                }
            }
        }
    }

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
        graph[v][u] = 1;  // Undirected graph
    }

    if (isBipartite(graph, n))
        printf("The graph is Bipartite.\n");
    else
        printf("The graph is NOT Bipartite.\n");

    return 0;
}
