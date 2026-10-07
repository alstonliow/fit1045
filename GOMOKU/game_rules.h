#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "board.h"
#include "gomoku-types.h"

/**
 * Gets the cell colour used for a side's stones.
 *
 * @param s the side
 * @return cell::BLACK for side::BLACK, cell::WHITE for side::WHITE
 */
cell cell_of(side s);

/**
 * Gets the other side.
 *
 * @param s the current side
 * @return the opponent of s
 */
side opponent(side s);

/**
 * Checks whether every cell on the board is occupied.
 *
 * @param b the board to check
 * @return true if no empty cells remain on b, otherwise false
 */
bool is_board_full(const board &b);

/**
 * Checks whether the stone at a position completes a winning line.
 *
 * @param b   the board to check
 * @param row the row of the stone just placed, must be in bounds
 * @param col the column of the stone just placed, must be in bounds
 * @return true if the stone at (row, col) is part of WIN_LENGTH or more
 *         same-coloured stones in a row, otherwise false
 */
bool check_win(const board &b, int row, int col);

#endif
