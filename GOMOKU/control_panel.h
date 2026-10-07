#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H

#include "splashkit.h"
#include "gomoku.h"
#include "layout.h"

/** What the player asked for in the control panel this frame. */
enum class panel_action
{
    NONE,
    UNDO,
    RESTART,
    TOGGLE_FULLSCREEN
};

/** Which sidebar sections are expanded. */
struct section_state
{
    bool mode;
    bool game;
    bool view;
    bool moves;
};

/** Settings the player can change in the control panel. */
struct panel_state
{
    game_mode mode;
    bool show_last_move;
    sidebar_settings sidebar;
    section_state open;
};

/**
 * Sets the interface colours to suit the dark sidebar. Call once, after
 * opening the window.
 */
void setup_panel_style();

/**
 * Creates the sidebar's interface elements inside a rectangle of the window.
 * Call between process_events() and draw_interface(), once per frame.
 *
 * @param game  the game to show (not modified)
 * @param state the settings, updated if the player changes them
 * @param area  where the sidebar goes, from compute_layout
 * @return the action the player chose, or panel_action::NONE
 */
panel_action draw_control_panel(const gomoku &game, panel_state &state, const rectangle &area);

/**
 * Creates the button in the activity bar that shows or hides the sidebar.
 *
 * @param state the settings, updated if the button is clicked
 * @param bar   the activity bar, from compute_layout
 */
void draw_activity_bar(panel_state &state, const rectangle &bar);

#endif
