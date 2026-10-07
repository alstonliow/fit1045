#ifndef BOARD_H
#define BOARD_H

#include "splashkit-arrays.h"
#include "gomoku-types.h"

class board
{
private:
    fixed_array<fixed_array<cell, BOARD_SIZE>, BOARD_SIZE> cells_;

public:
    board();
    cell cell_at(int row, int col) const;
    void set_cell(int row, int col, cell c);
    bool in_bounds(int row, int col) const;
    bool is_empty(int row, int col) const;
};

#endif
