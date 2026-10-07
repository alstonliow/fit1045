#include "gomoku.h"
#include "game_rules.h"

gomoku::gomoku() : current_(player::BLACK), state_(game_state::PLAYING)
{
}

bool gomoku::place(int row, int col)
{
    if (state_ != game_state::PLAYING)
        return false;
    if (!board_.in_bounds(row, col) || !board_.is_empty(row, col))
        return false;

    board_.set_cell(row, col, cell_of(current_));

    placement p;
    p.row = row;
    p.col = col;
    p.owner = current_;
    add(history_, p);

    if (check_win(board_, row, col))
        state_ = (current_ == player::BLACK) ? game_state::BLACK_WIN : game_state::WHITE_WIN;
    else if (is_board_full(board_))
        state_ = game_state::DRAW;
    else
        current_ = opponent(current_);

    return true;
}

bool gomoku::undo()
{
    if (is_empty_array(history_))
        return false;

    int last = length(history_) - 1;
    placement p = history_[last];

    board_.set_cell(p.row, p.col, cell::EMPTY);
    remove_at(history_, last);
    current_ = p.owner;
    state_ = game_state::PLAYING;
    return true;
}

void gomoku::reset()
{
    board_ = board();
    current_ = player::BLACK;
    state_ = game_state::PLAYING;
    clear(history_);
}

const board &gomoku::get_board() const
{
    return board_;
}

player gomoku::current_player() const
{
    return current_;
}

game_state gomoku::get_state() const
{
    return state_;
}

int gomoku::placement_count() const
{
    return length(history_);
}
