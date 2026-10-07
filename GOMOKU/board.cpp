#include "board.h"

board::board()
{
    for (int r = 0; r < BOARD_SIZE; r++)
        fill(cells_[r], cell::EMPTY);
}

cell board::cell_at(int row, int col) const
{
    return cells_[row][col];
}

void board::set_cell(int row, int col, cell c)
{
    cells_[row][col] = c;
}

bool board::in_bounds(int row, int col) const
{
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

bool board::is_empty(int row, int col) const
{
    return cells_[row][col] == cell::EMPTY;
}
