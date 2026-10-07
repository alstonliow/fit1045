#include "game_rules.h"

cell cell_of(side s)
{
    return (s == side::BLACK) ? cell::BLACK : cell::WHITE;
}

side opponent(side s)
{
    return (s == side::BLACK) ? side::WHITE : side::BLACK;
}

bool is_board_full(const board &b)
{
    for (int r = 0; r < BOARD_SIZE; r++)
        for (int c = 0; c < BOARD_SIZE; c++)
            if (b.is_empty(r, c))
                return false;
    return true;
}

bool check_win(const board &b, int row, int col)
{
    cell c = b.cell_at(row, col);
    if (c == cell::EMPTY)
        return false;

    // Horizontal, diagonal, vertical and anti-diagonal; the other half of
    // each line is covered by walking the opposite direction.
    const direction LINES[4] = {direction::E, direction::SE, direction::S, direction::SW};

    for (int i = 0; i < 4; i++)
    {
        direction d = LINES[i];
        int total = 1 + b.run_length(row, col, d, c) + b.run_length(row, col, opposite(d), c);
        if (total >= WIN_LENGTH)
            return true;
    }
    return false;
}
