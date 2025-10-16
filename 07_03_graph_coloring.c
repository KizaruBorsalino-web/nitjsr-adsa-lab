#include <stdio.h>
#include <stdbool.h>

#define V 4   // Number of vertices (you can change this)

// Function to print the color assignment
void printSolution(int color[]) {
    printf("Color assignment of vertices:\n");
    for (int i = 0; i < V; i++)
        printf("Vertex %d ---> Color %d\n", i + 1, color[i]);
}

// Function to check if the current color assignment is safe
bool isSafe(int v, bool graph[V][V], int color[], int c) {
    for (int i = 0; i < V; i++)
        if (graph[v][i] && color[i] == c)
            return false;  // Adjacent vertex has same color
    return true;
}

// Recursive utility function to solve graph coloring
bool graphColoringUtil(bool graph[V][V], int m, int color[], int v) {
    // Base case: If all vertices are assigned a color
    if (v == V)
        return true;

    // Try assigning each color from 1 to m
    for (int c = 1; c <= m; c++) {
        if (isSafe(v, graph, color, c)) {
            color[v] = c;

            // Recurse to assign colors to the rest of the vertices
            if (graphColoringUtil(graph, m, color, v + 1))
                return true;

            // Backtrack if assigning color c doesn't lead to a solution
            color[v] = 0;
        }
    }
    return false;
}

// Function to solve the graph coloring problem
bool graphColoring(bool graph[V][V], int m) {
    int color[V];
    for (int i = 0; i < V; i++)
        color[i] = 0;  // Initialize all vertices with 0 (no color)

    if (!graphColoringUtil(graph, m, color, 0)) {
        printf("Solution does not exist.\n");
        return false;
    }

    printSolution(color);
    return true;
}

// Main function
int main() {
    /* Example graph (Adjacency Matrix)
       1 — 2
       |  /
       | /
       3 — 4
    */
    bool graph[V][V] = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}
    };

    int m; // Number of colors
    printf("Enter number of colors: ");
    scanf("%d", &m);

    graphColoring(graph, m);
    return 0;
}
