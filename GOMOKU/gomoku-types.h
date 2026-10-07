#ifndef GOMOKU_TYPES_H
#define GOMOKU_TYPES_H

/** Number of rows and columns on the board. */
const int BOARD_SIZE = 15;

/** Number of stones in a row needed to win. */
const int WIN_LENGTH = 5;

/** What occupies a single board cell. */
enum class cell
{
    EMPTY,
    BLACK,
    WHITE
};

/** The two sides, by stone colour. Black moves first. */
enum class side
{
    BLACK,
    WHITE
};

/** Whether the game is ongoing or how it ended. */
enum class game_state
{
    PLAYING,
    BLACK_WIN,
    WHITE_WIN,
    DRAW
};

/** How the two sides are controlled. */
enum class game_mode
{
    PVP,
    PVC
};

/** One move: where a stone was placed and who placed it. */
struct placement
{
    int row;
    int col;
    side owner;
};

#endif
