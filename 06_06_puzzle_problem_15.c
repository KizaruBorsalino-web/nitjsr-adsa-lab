#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define N 4
#define MAX_STATE 3628800  // upper bound (not exact) for visited states

// Goal state
int GOAL_STATE[N * N] = {
    1, 2, 3, 4,
    5, 6, 7, 8,
    9,10,11,12,
    13,14,15,0
};

// Directions for movement (up, down, left, right)
int ROW[4] = {-1, 1, 0, 0};
int COL[4] = {0, 0, -1, 1};

typedef struct Node {
    int state[N * N];
    int g, h, f;
    struct Node *parent;
} Node;

// Min-heap node comparison
int compare_nodes(const void *a, const void *b) {
    Node *n1 = *(Node **)a;
    Node *n2 = *(Node **)b;
    return n1->f - n2->f;
}

// Manhattan distance heuristic
int manhattan_distance(int state[]) {
    int distance = 0;
    for (int i = 0; i < N * N; i++) {
        if (state[i] == 0) continue;
        int goal_pos = state[i] - 1;
        int curr_row = i / N, curr_col = i % N;
        int goal_row = goal_pos / N, goal_col = goal_pos % N;
        distance += abs(curr_row - goal_row) + abs(curr_col - goal_col);
    }
    return distance;
}

// Check if two states are equal
int equal_state(int a[], int b[]) {
    for (int i = 0; i < N * N; i++)
        if (a[i] != b[i]) return 0;
    return 1;
}

// Get neighbors (possible moves)
int get_neighbors(int state[][N * N]) {
    int zero_index = -1;
    for (int i = 0; i < N * N; i++)
        if (state[0][i] == 0) { zero_index = i; break; }

    int x = zero_index / N;
    int y = zero_index % N;
    int count = 0;

    for (int i = 0; i < 4; i++) {
        int new_x = x + ROW[i];
        int new_y = y + COL[i];
        if (new_x >= 0 && new_x < N && new_y >= 0 && new_y < N) {
            memcpy(state[count + 1], state[0], sizeof(int) * N * N);
            int new_index = new_x * N + new_y;
            int tmp = state[count + 1][zero_index];
            state[count + 1][zero_index] = state[count + 1][new_index];
            state[count + 1][new_index] = tmp;
            count++;
        }
    }
    return count;
}

// Print puzzle state
void print_board(int state[]) {
    for (int i = 0; i < N * N; i++) {
        if (i % N == 0) printf("\n");
        if (state[i] == 0) printf(" . ");
        else printf("%2d ", state[i]);
    }
    printf("\n\n");
}

// Reconstruct and print solution path
void reconstruct_path(Node *node) {
    if (node == NULL) return;
    reconstruct_path(node->parent);
    print_board(node->state);
}

// A* solver
void solve_15_puzzle(int start[]) {
    Node *open[100000]; // Priority queue
    int open_size = 0;
    Node *visited[MAX_STATE];
    int visited_size = 0;

    Node *root = (Node *)malloc(sizeof(Node));
    memcpy(root->state, start, sizeof(int) * N * N);
    root->parent = NULL;
    root->g = 0;
    root->h = manhattan_distance(root->state);
    root->f = root->g + root->h;
    open[open_size++] = root;

    while (open_size > 0) {
        qsort(open, open_size, sizeof(Node *), compare_nodes);
        Node *current = open[0];
        for (int i = 1; i < open_size; i++) open[i - 1] = open[i];
        open_size--;

        // If goal found
        if (equal_state(current->state, GOAL_STATE)) {
            printf("Solution found!\n");
            reconstruct_path(current);
            printf("Total moves: %d\n", current->g);
            return;
        }

        visited[visited_size++] = current;

        int neighbors[5][N * N];
        memcpy(neighbors[0], current->state, sizeof(int) * N * N);
        int count = get_neighbors(neighbors);

        for (int i = 1; i <= count; i++) {
            // Check if visited
            int already = 0;
            for (int v = 0; v < visited_size; v++) {
                if (equal_state(visited[v]->state, neighbors[i])) {
                    already = 1;
                    break;
                }
            }
            if (already) continue;

            Node *neighbor = (Node *)malloc(sizeof(Node));
            memcpy(neighbor->state, neighbors[i], sizeof(int) * N * N);
            neighbor->parent = current;
            neighbor->g = current->g + 1;
            neighbor->h = manhattan_distance(neighbor->state);
            neighbor->f = neighbor->g + neighbor->h;
            open[open_size++] = neighbor;
        }
    }

    printf("No solution found.\n");
}

// Main function
int main() {
    int start_state[N * N] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9,10,11,12,
        13,15,14,0  // solvable case
    };

    printf("Solving 15-puzzle...\n");
    solve_15_puzzle(start_state);
    return 0;
}
