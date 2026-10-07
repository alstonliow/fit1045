#include "gomoku.h"
#include "game_rules.h"

gomoku::gomoku() : current_(side::BLACK), state_(game_state::PLAYING)
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
    history_.add_node(p);

    if (check_win(board_, row, col))
        state_ = (current_ == side::BLACK) ? game_state::BLACK_WIN : game_state::WHITE_WIN;
    else if (is_board_full(board_))
        state_ = game_state::DRAW;
    else
        current_ = opponent(current_);

    return true;
}

bool gomoku::undo()
{
    if (history_.last == nullptr)
        return false;

    placement p = history_.last->data;

    board_.set_cell(p.row, p.col, cell::EMPTY);
    history_.remove(history_.last);
    current_ = p.owner;
    state_ = game_state::PLAYING;
    return true;
}

void gomoku::reset()
{
    board_.clear();
    current_ = side::BLACK;
    state_ = game_state::PLAYING;
    history_.clear();
}

const board &gomoku::get_board() const
{
    return board_;
}

side gomoku::current_side() const
{
    return current_;
}

game_state gomoku::get_state() const
{
    return state_;
}

int gomoku::placement_count() const
{
    return history_.fold(0, [](int count, const placement &) { return count + 1; });
}

placement gomoku::placement_at(int index) const
{
    const node<placement> *current = history_.first;
    for (int i = 0; i < index && current != nullptr; i++)
        current = current->next;

    if (index < 0 || current == nullptr)
        throw string("placement_at: index " + to_string(index) + " is out of range.");
    return current->data;
}

bool gomoku::last_placement(placement &p) const
{
    if (history_.last == nullptr)
        return false;

    p = history_.last->data;
    return true;
}
