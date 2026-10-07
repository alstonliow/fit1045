#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "board.h"
#include "gomoku-types.h"

cell   cell_of(player p);
player opponent(player p);
bool   is_board_full(const board &b);
bool   check_win(const board &b, int row, int col);

#endif
