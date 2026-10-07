#ifndef BOARD_H
#define BOARD_H

#include "splashkit-arrays.h"
#include "gomoku-types.h"

/**
 * The eight compass directions between neighbouring cells. Rows grow
 * downwards, so S is row + 1. The opposite of d is (d + 4) % 8.
 */
enum class direction
{
    E,
    SE,
    S,
    SW,
    W,
    NW,
    N,
    NE
};

/** Number of values in direction. */
const int DIRECTION_COUNT = 8;

/**
 * Gets the direction pointing the opposite way.
 *
 * @param d the direction to reverse
 * @return the direction 180 degrees from d
 */
direction opposite(direction d);

/**
 * One square of the board, linked to its up to eight neighbours.
 * A neighbour pointer is nullptr where the square is on the edge.
 */
struct cell_node
{
    cell state;
    cell_node *next[DIRECTION_COUNT];
};

/**
 * A BOARD_SIZE x BOARD_SIZE grid of cells. Knows nothing about turns or rules.
 *
 * Every node points into this board's own nodes_ array, so a board cannot be
 * copied or assigned: the copy's pointers would still refer to the original.
 */
class board
{
private:
    fixed_array<fixed_array<cell_node, BOARD_SIZE>, BOARD_SIZE> nodes_;

public:
    /**
     * Creates a board with every cell empty and links each node to its
     * neighbours.
     */
    board();

    board(const board &) = delete;
    board &operator=(const board &) = delete;

    /**
     * Sets every cell back to empty. The neighbour links are unchanged.
     */
    void clear();

    /**
     * Gets the contents of a cell.
     *
     * @param row the row index, must be in bounds
     * @param col the column index, must be in bounds
     * @return the cell at (row, col)
     */
    cell cell_at(int row, int col) const;

    /**
     * Sets the contents of a cell.
     *
     * @param row the row index, must be in bounds
     * @param col the column index, must be in bounds
     * @param c   the value to store at (row, col)
     */
    void set_cell(int row, int col, cell c);

    /**
     * Checks whether a position lies on the board.
     *
     * @param row the row index to check
     * @param col the column index to check
     * @return true if 0 <= row, col < BOARD_SIZE, otherwise false
     */
    bool in_bounds(int row, int col) const;

    /**
     * Checks whether a cell has no stone on it.
     *
     * @param row the row index, must be in bounds
     * @param col the column index, must be in bounds
     * @return true if the cell at (row, col) is cell::EMPTY, otherwise false
     */
    bool is_empty(int row, int col) const;

    /**
     * Counts consecutive cells equal to c, starting next to (row, col) and
     * following the neighbour links in direction d. The cell at (row, col)
     * itself is not counted.
     *
     * @param row the starting row, must be in bounds
     * @param col the starting column, must be in bounds
     * @param d   the direction to walk
     * @param c   the value to count
     * @return the number of matching cells before a different cell or the edge
     */
    int run_length(int row, int col, direction d, cell c) const;
};

#endif
