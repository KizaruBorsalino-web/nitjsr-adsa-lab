#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// ---------- Data structures ----------
int time_counter = 0;

typedef struct {
    int u, v;
} Edge;

// ---------- Function prototypes ----------
void SCCUtil(int u, int disc[], int low[], bool stackMember[], int stack[], int *stackTop, int adj[MAX][MAX], int V);
void findSCCs(int adj[MAX][MAX], int V);

void APBUtil(int u, int parent[], int disc[], int low[], bool visited[], bool isAP[], int adj[MAX][MAX], int V);
void findAPsAndBridges(int adj[MAX][MAX], int V);

// ---------- Strongly Connected Components (Tarjan’s algorithm) ----------
void SCCUtil(int u, int disc[], int low[], bool stackMember[], int stack[], int *stackTop, int adj[MAX][MAX], int V) {
    static int time = 0;
    disc[u] = low[u] = ++time;
    stack[++(*stackTop)] = u;
    stackMember[u] = true;

    for (int v = 0; v < V; v++) {
        if (adj[u][v]) {
            if (disc[v] == -1) {
                SCCUtil(v, disc, low, stackMember, stack, stackTop, adj, V);
                low[u] = (low[u] < low[v]) ? low[u] : low[v];
            } else if (stackMember[v]) {
                low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
            }
        }
    }

    // Head node found, print SCC
    if (low[u] == disc[u]) {
        printf("SCC: ");
        while (stack[*stackTop] != u) {
            printf("%d ", stack[*stackTop]);
            stackMember[stack[*stackTop]] = false;
            (*stackTop)--;
        }
        printf("%d\n", stack[*stackTop]);
        stackMember[stack[*stackTop]] = false;
        (*stackTop)--;
    }
}

void findSCCs(int adj[MAX][MAX], int V) {
    int disc[MAX], low[MAX], stack[MAX];
    bool stackMember[MAX];

    for (int i = 0; i < V; i++) {
        disc[i] = -1;
        low[i] = -1;
        stackMember[i] = false;
    }

    int stackTop = -1;
    for (int i = 0; i < V; i++) {
        if (disc[i] == -1)
            SCCUtil(i, disc, low, stackMember, stack, &stackTop, adj, V);
    }
}

// ---------- Articulation Points and Bridges ----------
void APBUtil(int u, int parent[], int disc[], int low[], bool visited[], bool isAP[], int adj[MAX][MAX], int V) {
    static int time = 0;
    visited[u] = true;
    disc[u] = low[u] = ++time;
    int children = 0;

    for (int v = 0; v < V; v++) {
        if (!adj[u][v]) continue;

        if (!visited[v]) {
            children++;
            parent[v] = u;
            APBUtil(v, parent, disc, low, visited, isAP, adj, V);

            low[u] = (low[u] < low[v]) ? low[u] : low[v];

            // (1) u is root of DFS tree and has two or more children.
            if (parent[u] == -1 && children > 1)
                isAP[u] = true;

            // (2) If u is not root and low[v] >= disc[u].
            if (parent[u] != -1 && low[v] >= disc[u])
                isAP[u] = true;

            // (3) Bridge condition
            if (low[v] > disc[u])
                printf("Bridge: (%d - %d)\n", u, v);
        }
        else if (v != parent[u]) {
            low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
        }
    }
}

void findAPsAndBridges(int adj[MAX][MAX], int V) {
    int disc[MAX], low[MAX], parent[MAX];
    bool visited[MAX], isAP[MAX];

    for (int i = 0; i < V; i++) {
        visited[i] = false;
        isAP[i] = false;
        parent[i] = -1;
    }

    for (int i = 0; i < V; i++)
        if (!visited[i])
            APBUtil(i, parent, disc, low, visited, isAP, adj, V);

    printf("\nArticulation Points:\n");
    for (int i = 0; i < V; i++)
        if (isAP[i])
            printf("%d ", i);
    printf("\n");
}

// ---------- Main Function ----------
int main() {
    int V, E;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);

    int adj[MAX][MAX] = {0};
    printf("Enter edges (u v):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;   // directed edge
        adj[v][u] = 1;   // comment this if graph is directed
    }

    printf("\n--- Strongly Connected Components ---\n");
    findSCCs(adj, V);

    printf("\n--- Articulation Points and Bridges ---\n");
    findAPsAndBridges(adj, V);

    return 0;
}
