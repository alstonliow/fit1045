#ifndef RESULT_OVERLAY_H
#define RESULT_OVERLAY_H

#include "splashkit.h"
#include "gomoku.h"
#include "control_panel.h"

/** The end-of-game card shown over the board. */
struct result_overlay
{
    int frames;       // frames since the game ended, 0 while playing
    bool dismissed;   // the player chose to look at the board instead
    bool font_loaded; // false means the small default font is used
    font title_font;
};

/**
 * Creates the overlay and loads its font from Resources/fonts.
 *
 * @return an overlay with no game over yet
 */
result_overlay new_result_overlay();

/**
 * Advances the overlay's animation by one frame, and resets it when a
 * game is in progress (after Restart or Undo).
 *
 * @param overlay the overlay to update
 * @param game    the game being shown
 */
void update_result_overlay(result_overlay &overlay, const gomoku &game);

/**
 * Draws the result card in the middle of the board area once the game is
 * over. Call between process_events() and draw_interface(), after the
 * board is drawn.
 *
 * @param overlay  the overlay, updated if "View board" or "Show result" is clicked
 * @param game     the finished game
 * @param area     the board area of the window
 * @param mode     the game mode, to word the title for PvC
 * @param computer the side the computer plays
 * @return RESTART or UNDO if those buttons were clicked, otherwise NONE
 */
panel_action draw_result_overlay(result_overlay &overlay, const gomoku &game, const rectangle &area,
                                 game_mode mode, side computer);

#endif
