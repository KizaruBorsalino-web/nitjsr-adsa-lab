def solve_n_queens(n):
    """
    Solves the N-Queens problem using backtracking.
    
    :param n: Size of the board (n x n)
    :return: List of solutions (each solution is a list of queen positions)
    """
    solutions = []
    board = [-1] * n  # board[i] = column index of the queen placed in row i

    def is_safe(row, col):
        # Check for conflicts with previously placed queens
        for prev_row in range(row):
            if (board[prev_row] == col or  # same column
                abs(board[prev_row] - col) == abs(prev_row - row)):  # same diagonal
                return False
        return True

    def backtrack(row):
        if row == n:
            # All queens placed successfully
            solutions.append(board[:])
            return
        for col in range(n):
            if is_safe(row, col):
                board[row] = col
                backtrack(row + 1)
                board[row] = -1  # backtrack

    backtrack(0)
    return solutions


def print_solutions(solutions):
    for sol_num, sol in enumerate(solutions, start=1):
        print(f"Solution {sol_num}:")
        for row in sol:
            line = ['.'] * len(sol)
            line[row] = 'Q'
            print(' '.join(line))
        print()

# Example usage
if __name__ == "__main__":
    n = 4
    solutions = solve_n_queens(n)
    print(f"Total solutions for {n}-Queens: {len(solutions)}\n")
    print_solutions(solutions)
