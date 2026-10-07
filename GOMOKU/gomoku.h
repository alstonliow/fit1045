#ifndef GOMOKU_H
#define GOMOKU_H

#include "splashkit-arrays.h"
#include "gomoku-types.h"
#include "board.h"

class gomoku
{
private:
    board board_;
    player current_;
    game_state state_;
    dynamic_array<placement> history_;

public:
    gomoku();

    bool place(int row, int col);
    bool undo();
    void reset();

    const board &get_board() const;
    player current_player() const;
    game_state get_state() const;
    int placement_count() const;
};

#endif
