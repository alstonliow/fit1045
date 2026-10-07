#ifndef AI_H
#define AI_H

#include "board.h"
#include "gomoku-types.h"

/** Score for each kind of line; "open" means both ends are empty. */
struct eval_weights
{
    int five;
    int open_four;
    int closed_four;
    int open_three;
    int closed_three;
    int open_two;
    int closed_two;
};

/** Everything that tunes how the computer searches. */
struct ai_settings
{
    int depth;          // moves looked ahead; at least 2 to see the opponent's reply
    int max_candidates; // moves tried at each step, best first
    bool use_pruning;   // alpha-beta on or off (off is only for testing)
    eval_weights weights;
};

/** The computer's chosen move and how it was found. */
struct search_result
{
    bool found;     // false only if the board is full
    placement best;
    int score;      // from the computer's point of view
    long nodes;     // positions searched
};

/**
 * Gets the default search settings.
 *
 * @return depth 3, 12 candidates per step, pruning on
 */
ai_settings default_ai_settings();

/**
 * Scores a position for one side: its lines minus the opponent's lines.
 *
 * @param b  the board to score
 * @param me the side to score for
 * @param w  the score of each kind of line
 * @return a positive score if the position favours me
 */
int evaluate_board(const board &b, side me, const eval_weights &w);

/**
 * Chooses the computer's move. The board passed in is not changed;
 * the search works on its own copy.
 *
 * @param source   the current position
 * @param me       the side the computer plays
 * @param settings how deep and how wide to search
 * @return the best move found
 */
search_result choose_placement(const board &source, side me, const ai_settings &settings);

#endif
