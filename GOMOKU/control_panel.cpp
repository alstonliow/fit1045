#include "control_panel.h"
#include "splashkit.h"

/**
 * Gets the display name for a side.
 *
 * @param s the side to name
 * @return "Black (X)" or "White (O)"
 */
static string side_name(side s)
{
    return (s == side::BLACK) ? "Black (X)" : "White (O)";
}

/**
 * Gets a move in the same notation the CLI accepts, such as "h8".
 *
 * @param p the move to name
 * @return the column letter followed by the 1-based row number
 */
static string placement_name(const placement &p)
{
    return string(1, (char)('a' + p.col)) + to_string(p.row + 1);
}

/**
 * Gets the display name for a game mode.
 *
 * @param mode the mode to name
 * @return a short description of who controls each side
 */
static string mode_name(game_mode mode)
{
    return (mode == game_mode::PVP) ? "Player vs Player" : "Player vs Computer";
}

/**
 * Gets a one-line summary of whose turn it is or how the game ended.
 *
 * @param game the game to describe
 * @return the status line shown at the top of the panel
 */
static string status_text(const gomoku &game)
{
    switch (game.get_state())
    {
    case game_state::BLACK_WIN:
        return "Black (X) wins!";
    case game_state::WHITE_WIN:
        return "White (O) wins!";
    case game_state::DRAW:
        return "It's a draw.";
    default:
        return side_name(game.current_side()) + " to move";
    }
}

/**
 * Whether a mode can be chosen yet. Change this when the AI is written.
 *
 * @param mode the mode to check
 * @return true if the mode's button should be enabled
 */
static bool mode_available(game_mode mode)
{
    return mode == game_mode::PVP;
}

/**
 * Creates a section heading that expands or collapses when clicked.
 * SplashKit's header() always starts collapsed and can't be opened from
 * code, so this keeps the open/closed state in panel_state instead.
 *
 * @param title the section name
 * @param open  whether the section is expanded, toggled when clicked
 * @return true if the section's contents should be shown
 */
static bool section(const string &title, bool &open)
{
    if (button((open ? "v  " : ">  ") + title))
        open = !open;
    return open;
}

/**
 * Creates the mode heading and the PvP / PvC buttons.
 *
 * @param state the settings, updated if a mode button is clicked
 */
static void draw_mode_section(panel_state &state)
{
    if (!section("Mode", state.open.mode))
        return;

    paragraph("Current: " + mode_name(state.mode));

    start_custom_layout();
    split_into_columns(2);

    if (button("PvP"))
        state.mode = game_mode::PVP;

    if (!mode_available(game_mode::PVC))
        disable_interface();
    if (button("PvC"))
        state.mode = game_mode::PVC;
    enable_interface();

    reset_layout();
}

/**
 * Creates the last-stone checkbox and the Undo / Restart buttons.
 *
 * @param state the settings, updated if the checkbox is toggled
 * @return the button the player clicked, or panel_action::NONE
 */
static panel_action draw_game_section(panel_state &state)
{
    panel_action action = panel_action::NONE;

    if (section("Game", state.open.game))
    {
        state.show_last_move = checkbox("Mark last stone", state.show_last_move);

        start_custom_layout();
        split_into_columns(2);
        if (button("Undo"))
            action = panel_action::UNDO;
        if (button("Restart"))
            action = panel_action::RESTART;
        reset_layout();
    }
    return action;
}

/**
 * Creates the controls for where the sidebar sits and for fullscreen.
 *
 * @param state the settings, updated if the player changes them
 * @return TOGGLE_FULLSCREEN if that button was clicked, otherwise NONE
 */
static panel_action draw_view_section(panel_state &state)
{
    panel_action action = panel_action::NONE;

    if (section("View", state.open.view))
    {
        state.sidebar.on_left = checkbox("Sidebar on left", state.sidebar.on_left);

        start_custom_layout();
        split_into_columns(2);
        if (button("Hide sidebar"))
            state.sidebar.visible = false;
        if (button("Fullscreen"))
            action = panel_action::TOGGLE_FULLSCREEN;
        reset_layout();

        paragraph("Ctrl/Cmd+B toggles the sidebar, F11 toggles fullscreen. Drag the divider to resize.");
    }
    return action;
}

/**
 * Creates a scrolling list of every move, newest first.
 *
 * @param game   the game whose history to list
 * @param state  the settings holding whether the section is open
 * @param height the height in pixels of the list
 */
static void draw_history_section(const gomoku &game, panel_state &state, int height)
{
    if (!section("Moves", state.open.moves))
        return;

    start_inset("Move list", height);
    for (int i = game.placement_count() - 1; i >= 0; i--)
    {
        placement p = game.placement_at(i);
        label_element(to_string(i + 1) + ". " + side_name(p.owner) + "  " + placement_name(p));
    }
    end_inset("Move list");
}

/** Shortest the move list gets, however short the window. */
const int MIN_MOVE_LIST_HEIGHT = 120;

/** Rough height of everything in the sidebar above the move list. */
const int SIDEBAR_CONTENT_ABOVE_MOVES = 420;

panel_action draw_control_panel(const gomoku &game, panel_state &state, const rectangle &area)
{
    panel_action action = panel_action::NONE;

    // The move list takes whatever height the other sections leave; the
    // sidebar scrolls if the window is too short for everything.
    int list_height = (int)area.height - SIDEBAR_CONTENT_ABOVE_MOVES;
    if (list_height < MIN_MOVE_LIST_HEIGHT)
        list_height = MIN_MOVE_LIST_HEIGHT;

    start_inset("Sidebar", area);
    paragraph(status_text(game));
    draw_mode_section(state);

    panel_action game_action = draw_game_section(state);
    if (game_action != panel_action::NONE)
        action = game_action;

    panel_action view_action = draw_view_section(state);
    if (view_action != panel_action::NONE)
        action = view_action;

    draw_history_section(game, state, list_height);
    end_inset("Sidebar");

    return action;
}

void setup_panel_style()
{
    set_interface_style(FLAT_DARK_STYLE);
    // Text outside a framed panel uses the root colour, which defaults to
    // black and is unreadable on the dark sidebar.
    set_interface_root_text_color(rgb_color(204, 204, 204));
}

void draw_activity_bar(panel_state &state, const rectangle &bar)
{
    // The arrow points the way the sidebar will move when clicked.
    bool toward_edge = state.sidebar.visible;
    bool points_left = state.sidebar.on_left ? toward_edge : !toward_edge;

    rectangle r = rectangle_from(bar.x + 4, bar.y + 8, bar.width - 8, bar.width - 8);
    if (button(points_left ? "<" : ">", r))
        state.sidebar.visible = !state.sidebar.visible;
}
