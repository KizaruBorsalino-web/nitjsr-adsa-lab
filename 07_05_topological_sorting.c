#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Adjacency list node
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Graph structure
typedef struct Graph {
    int numVertices;
    Node** adjLists;
    int* visited;
} Graph;

// Stack for storing topological order
typedef struct Stack {
    int items[MAX];
    int top;
} Stack;

// Function to create a node
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Add edge to directed graph
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

// Create a stack
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

// Push into stack
void push(Stack* stack, int value) {
    stack->items[++stack->top] = value;
}

// Pop from stack
int pop(Stack* stack) {
    return stack->items[stack->top--];
}

// DFS-based function for topological sorting
void topologicalSortUtil(Graph* graph, int v, Stack* stack) {
    graph->visited[v] = 1;

    Node* temp = graph->adjLists[v];
    while (temp) {
        int connectedVertex = temp->vertex;
        if (!graph->visited[connectedVertex])
            topologicalSortUtil(graph, connectedVertex, stack);
        temp = temp->next;
    }

    push(stack, v);
}

// Function to perform Topological Sort
void topologicalSort(Graph* graph) {
    Stack* stack = createStack();

    for (int i = 0; i < graph->numVertices; i++) {
        if (!graph->visited[i])
            topologicalSortUtil(graph, i, stack);
    }

    printf("Topological Sort Order: ");
    while (stack->top != -1)
        printf("%d ", pop(stack));
    printf("\n");
}

// Main function
int main() {
    int V = 6;
    Graph* graph = createGraph(V);

    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    printf("Topological Sorting of the given graph:\n");
    topologicalSort(graph);

    return 0;
}
