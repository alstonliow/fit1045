#ifndef RENDERER_H
#define RENDERER_H

#include "splashkit.h"
#include "gomoku.h"

/**
 * Where the board grid sits on screen, worked out from the area it must fit.
 */
struct board_geometry
{
    double left; // x of column 0
    double top;  // y of row 0
    double cell; // pixels between grid lines
};

/**
 * Fits the largest square board, with room for its labels, into an area.
 *
 * @param area the part of the window the board may use
 * @return the grid position and spacing
 */
board_geometry fit_board(const rectangle &area);

/**
 * Fills the area with the board colour and draws the grid and stones.
 * Does not refresh the window.
 *
 * @param game           the game to draw
 * @param area           the part of the window the board may use
 * @param geo            the grid position, from fit_board(area)
 * @param show_last_move whether to mark the most recent stone
 */
void draw_game(const gomoku &game, const rectangle &area, const board_geometry &geo, bool show_last_move);

/**
 * Converts a position in the window to the nearest board intersection.
 *
 * @param geo the grid position
 * @param x   the x position in pixels
 * @param y   the y position in pixels
 * @param row set to the row on success
 * @param col set to the column on success
 * @return true if the position is on the board, otherwise false
 */
bool pixel_to_cell(const board_geometry &geo, double x, double y, int &row, int &col);

#endif
