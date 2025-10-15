import heapq
import copy

# Size of the puzzle
N = 4
GOAL_STATE = [1, 2, 3, 4,
              5, 6, 7, 8,
              9,10,11,12,
              13,14,15,0]  # 0 represents the blank space

# Directions for movement
ROW = [-1, 1, 0, 0]  # up, down
COL = [0, 0, -1, 1]  # left, right

# Heuristic: Manhattan distance
def manhattan_distance(state):
    distance = 0
    for i in range(N * N):
        if state[i] == 0:
            continue
        goal_pos = state[i] - 1
        curr_row, curr_col = i // N, i % N
        goal_row, goal_col = goal_pos // N, goal_pos % N
        distance += abs(curr_row - goal_row) + abs(curr_col - goal_col)
    return distance

# Node representation for priority queue
class Node:
    def __init__(self, state, parent=None, g=0):
        self.state = state
        self.parent = parent
        self.g = g  # Cost to reach this node
        self.h = manhattan_distance(state)
        self.f = self.g + self.h

    def __lt__(self, other):  # Needed for heapq
        return self.f < other.f

def get_neighbors(state):
    neighbors = []
    zero_index = state.index(0)
    x, y = zero_index // N, zero_index % N

    for i in range(4):
        new_x = x + ROW[i]
        new_y = y + COL[i]

        if 0 <= new_x < N and 0 <= new_y < N:
            new_index = new_x * N + new_y
            new_state = state[:]
            # Swap 0 with the target tile
            new_state[zero_index], new_state[new_index] = new_state[new_index], new_state[zero_index]
            neighbors.append(new_state)

    return neighbors

# Reconstruct the path from goal to start
def reconstruct_path(node):
    path = []
    while node:
        path.append(node.state)
        node = node.parent
    return path[::-1]  # Reverse the path

def is_solvable(puzzle):
    """
    Check if a 15-puzzle is solvable.
    """
    inv_count = 0
    puzzle = [x for x in puzzle if x != 0]
    for i in range(len(puzzle)):
        for j in range(i + 1, len(puzzle)):
            if puzzle[i] > puzzle[j]:
                inv_count += 1

    # Blank row counting from bottom (0-based index from bottom)
    blank_row = 3 - (puzzle.index(0) // 4)

    # If grid width is odd, return true if inversion count is even.
    if N % 2 != 0:
        return inv_count % 2 == 0
    else:
        # If grid width is even, return true if:
        # the blank is on an even row counting from bottom and inv_count is odd
        # OR the blank is on an odd row from bottom and inv_count is even
        return (blank_row % 2 == 0) == (inv_count % 2 != 0)

def solve_15_puzzle(start_state):
    if not is_solvable(start_state):
        print("This puzzle is not solvable.")
        return []

    visited = set()
    pq = []
    root = Node(start_state)
    heapq.heappush(pq, root)

    while pq:
        current = heapq.heappop(pq)
        visited.add(tuple(current.state))

        if current.state == GOAL_STATE:
            return reconstruct_path(current)

        for neighbor in get_neighbors(current.state):
            if tuple(neighbor) not in visited:
                neighbor_node = Node(neighbor, current, current.g + 1)
                heapq.heappush(pq, neighbor_node)

    return []  # No solution found

def print_board(state):
    for i in range(0, N*N, N):
        row = state[i:i+N]
        print(' '.join(f'{x:2}' if x != 0 else ' .' for x in row))
    print()

# Example usage
if __name__ == "__main__":
    # A simple test case (takes only a few moves)
    start_state = [1, 2, 3, 4,
                   5, 6, 7, 8,
                   9, 10, 11, 12,
                   13, 15, 14, 0]  # Simple solvable case

    solution_path = solve_15_puzzle(start_state)

    if solution_path:
        print(f"Solution found in {len(solution_path) - 1} moves:\n")
        for step, state in enumerate(solution_path):
            print(f"Step {step}:")
            print_board(state)
    else:
        print("No solution found.")
