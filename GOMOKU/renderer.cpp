#include "renderer.h"
#include <cmath>

/** Stone radius as a fraction of the grid spacing. */
const double STONE_SCALE = 0.43;

/** Star point and last-move marker radius as a fraction of the grid spacing. */
const double DOT_SCALE = 0.1;

/** Pixel size of one character in SplashKit's default font. */
const int CHAR_PX = 8;

/**
 * Gets the x position of a column's grid line.
 *
 * @param geo the grid position
 * @param col the column index
 * @return the x position in pixels
 */
static double col_x(const board_geometry &geo, int col)
{
    return geo.left + col * geo.cell;
}

/**
 * Gets the y position of a row's grid line.
 *
 * @param geo the grid position
 * @param row the row index
 * @return the y position in pixels
 */
static double row_y(const board_geometry &geo, int row)
{
    return geo.top + row * geo.cell;
}

board_geometry fit_board(const rectangle &area)
{
    // BOARD_SIZE - 1 gaps between lines, plus one cell of margin each side
    // for the labels.
    double short_side = std::min(area.width, area.height);
    board_geometry geo;
    geo.cell = std::floor(short_side / (BOARD_SIZE + 1));

    double grid = geo.cell * (BOARD_SIZE - 1);
    geo.left = std::floor(area.x + (area.width - grid) / 2);
    geo.top = std::floor(area.y + (area.height - grid) / 2);
    return geo;
}

/**
 * Draws the grid lines and the five star points.
 *
 * @param geo the grid position
 */
static void draw_grid(const board_geometry &geo)
{
    double first_x = col_x(geo, 0), last_x = col_x(geo, BOARD_SIZE - 1);
    double first_y = row_y(geo, 0), last_y = row_y(geo, BOARD_SIZE - 1);

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        draw_line(COLOR_BLACK, first_x, row_y(geo, i), last_x, row_y(geo, i));
        draw_line(COLOR_BLACK, col_x(geo, i), first_y, col_x(geo, i), last_y);
    }

    // Star points for a 15 x 15 board
    const int STARS[5][2] = {{3, 3}, {3, 11}, {7, 7}, {11, 3}, {11, 11}};
    for (int i = 0; i < 5; i++)
        fill_circle(COLOR_BLACK, col_x(geo, STARS[i][1]), row_y(geo, STARS[i][0]), geo.cell * DOT_SCALE);
}

/**
 * Draws column letters along the top and row numbers down the left.
 *
 * @param geo the grid position
 */
static void draw_labels(const board_geometry &geo)
{
    double gap = geo.cell * 0.6;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        string letter(1, (char)('A' + i));
        string number = to_string(i + 1);
        draw_text(letter, COLOR_BLACK, col_x(geo, i) - CHAR_PX / 2, geo.top - gap - CHAR_PX / 2);
        draw_text(number, COLOR_BLACK, geo.left - gap - CHAR_PX * (int)number.length() / 2.0, row_y(geo, i) - CHAR_PX / 2);
    }
}

/**
 * Draws one stone, or nothing if the cell is empty.
 *
 * @param geo the grid position
 * @param c   the cell contents
 * @param row the row of the cell
 * @param col the column of the cell
 */
static void draw_stone(const board_geometry &geo, cell c, int row, int col)
{
    double x = col_x(geo, col);
    double y = row_y(geo, row);
    double radius = geo.cell * STONE_SCALE;

    if (c == cell::BLACK)
    {
        fill_circle(COLOR_BLACK, x, y, radius);
    }
    else if (c == cell::WHITE)
    {
        fill_circle(COLOR_WHITE, x, y, radius);
        draw_circle(COLOR_BLACK, x, y, radius);
    }
}

void draw_game(const gomoku &game, const rectangle &area, const board_geometry &geo, bool show_last_move)
{
    fill_rectangle(rgb_color(222, 184, 100), area.x, area.y, area.width, area.height);
    draw_grid(geo);
    draw_labels(geo);

    const board &b = game.get_board();
    for (int r = 0; r < BOARD_SIZE; r++)
        for (int c = 0; c < BOARD_SIZE; c++)
            draw_stone(geo, b.cell_at(r, c), r, c);

    placement last;
    if (show_last_move && game.last_placement(last))
        fill_circle(COLOR_RED, col_x(geo, last.col), row_y(geo, last.row), geo.cell * DOT_SCALE);
}

bool pixel_to_cell(const board_geometry &geo, double x, double y, int &row, int &col)
{
    if (geo.cell <= 0)
        return false;

    col = (int)std::lround((x - geo.left) / geo.cell);
    row = (int)std::lround((y - geo.top) / geo.cell);

    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}
