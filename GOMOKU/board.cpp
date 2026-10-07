#include "board.h"

/** Row step for each direction, in the order of the direction enum. */
const int DR[DIRECTION_COUNT] = {0, 1, 1, 1, 0, -1, -1, -1};

/** Column step for each direction, in the order of the direction enum. */
const int DC[DIRECTION_COUNT] = {1, 1, 0, -1, -1, -1, 0, 1};

direction opposite(direction d)
{
    return (direction)(((int)d + DIRECTION_COUNT / 2) % DIRECTION_COUNT);
}

board::board()
{
    for (int r = 0; r < BOARD_SIZE; r++)
        for (int c = 0; c < BOARD_SIZE; c++)
        {
            nodes_[r][c].state = cell::EMPTY;
            for (int d = 0; d < DIRECTION_COUNT; d++)
            {
                int nr = r + DR[d];
                int nc = c + DC[d];
                nodes_[r][c].next[d] = in_bounds(nr, nc) ? &nodes_[nr][nc] : nullptr;
            }
        }
}

void board::clear()
{
    for (int r = 0; r < BOARD_SIZE; r++)
        for (int c = 0; c < BOARD_SIZE; c++)
            nodes_[r][c].state = cell::EMPTY;
}

cell board::cell_at(int row, int col) const
{
    return nodes_[row][col].state;
}

void board::set_cell(int row, int col, cell c)
{
    nodes_[row][col].state = c;
}

bool board::in_bounds(int row, int col) const
{
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

bool board::is_empty(int row, int col) const
{
    return nodes_[row][col].state == cell::EMPTY;
}

int board::run_length(int row, int col, direction d, cell c) const
{
    int count = 0;
    for (const cell_node *p = nodes_[row][col].next[(int)d]; p && p->state == c; p = p->next[(int)d])
        count++;
    return count;
}
