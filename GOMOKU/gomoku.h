#ifndef GOMOKU_H
#define GOMOKU_H

#include "splashkit-arrays.h"
#include "gomoku-types.h"
#include "board.h"
#include "list.hpp"

/**
 * A game of Gomoku: the board, whose turn it is, the result and move history.
 */
class gomoku
{
private:
    board board_;
    side current_;
    game_state state_;
    linked_list<placement> history_;

public:
    /**
     * Starts a new game with an empty board and Black to move.
     */
    gomoku();

    /**
     * Places the current side's stone, then checks for a win or draw.
     * If the game continues, the turn passes to the opponent.
     *
     * @param row the row to place the stone in
     * @param col the column to place the stone in
     * @return true if the stone was placed; false if the game is over,
     *         (row, col) is off the board, or the cell is occupied
     */
    bool place(int row, int col);

    /**
     * Takes back the last move and gives the turn back to whoever made it.
     *
     * @return true if a move was undone, false if there is nothing to undo
     */
    bool undo();

    /**
     * Clears the board and history and starts again with Black to move.
     */
    void reset();

    /**
     * Gets the game board.
     *
     * @return a read-only reference to the board
     */
    const board &get_board() const;

    /**
     * Gets the side whose turn it is.
     *
     * @return the side to move, or the winner once the game is won
     */
    side current_side() const;

    /**
     * Gets the current state of the game.
     *
     * @return whether the game is ongoing, won by Black or White, or drawn
     */
    game_state get_state() const;

    /**
     * Gets the number of moves made so far.
     *
     * @return the number of stones on the board
     */
    int placement_count() const;

    /**
     * Gets one of the moves made so far. Walks the history from the first
     * move, so it takes time proportional to index.
     *
     * @param index the move number, from 0 (first move) to placement_count() - 1
     * @return the stone placed in that move
     */
    placement placement_at(int index) const;

    /**
     * Gets the most recent move.
     *
     * @param p set to the last stone placed, if there is one
     * @return true if at least one move has been made, otherwise false
     */
    bool last_placement(placement &p) const;
};

#endif
