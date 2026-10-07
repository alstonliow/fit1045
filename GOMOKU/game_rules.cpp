#include "game_rules.h"

cell cell_of(player p)
{
    return (p == player::BLACK) ? cell::BLACK : cell::WHITE;
}

player opponent(player p)
{
    return (p == player::BLACK) ? player::WHITE : player::BLACK;
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
    // TODO：你自己写。提示：沿 4 个方向 (0,1) (1,0) (1,1) (1,-1)，
    // 从 (row, col) 往正反两边数连续同色格，总数 >= WIN_LENGTH 即胜
    return false;
}
