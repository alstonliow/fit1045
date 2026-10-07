#ifndef GOMOKU_TYPES_H
#define GOMOKU_TYPES_H

const int BOARD_SIZE = 15;
const int WIN_LENGTH = 5;

enum class cell
{
    EMPTY,
    BLACK,
    WHITE
};

enum class player
{
    BLACK,
    WHITE
};

enum class game_state
{
    PLAYING,
    BLACK_WIN,
    WHITE_WIN,
    DRAW
};

struct placement
{
    int row;
    int col;
    player owner;
};

#endif
