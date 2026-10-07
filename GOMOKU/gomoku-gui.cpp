#include "splashkit.h"
#include "gomoku.h"
#include "ai.h"
#include "app_window.h"
#include "layout.h"
#include "renderer.h"
#include "control_panel.h"
#include "result_overlay.h"

/**
 * Places a stone if the player clicked inside the board area.
 *
 * @param game the game to place the stone in
 * @param area the board area of the window
 * @param geo  where the grid is drawn inside the area
 */
void handle_board_click(gomoku &game, const rectangle &area, const board_geometry &geo)
{
    
    if (!mouse_clicked(LEFT_BUTTON) || !point_in_rectangle(mouse_position(), area))
        return;

    int row, col;
    if (pixel_to_cell(geo, mouse_x(), mouse_y(), row, col))
        game.place(row, col);
}

/**
 * Handles the keyboard shortcuts: Ctrl/Cmd+B toggles the sidebar, F11
 * toggles fullscreen, Escape leaves fullscreen.
 *
 * @param win   the window to switch to or from fullscreen
 * @param state the settings holding the sidebar visibility
 */
void handle_shortcuts(app_window &win, panel_state &state)
{
    bool modifier = key_down(LEFT_CTRL_KEY) || key_down(RIGHT_CTRL_KEY) ||
                    key_down(LEFT_SUPER_KEY) || key_down(RIGHT_SUPER_KEY);

    if (modifier && key_typed(B_KEY))
        state.sidebar.visible = !state.sidebar.visible;

    if (key_typed(F11_KEY) || (key_typed(ESCAPE_KEY) && window_is_fullscreen(win.wnd)))
        toggle_fullscreen(win);
}

/**
 * Carries out the action chosen in the control panel. Against the
 * computer, Undo takes back moves until it is the player's turn again.
 *
 * @param game     the game to change
 * @param win      the window, for fullscreen
 * @param action   what the player asked for
 * @param mode     the current game mode
 * @param computer the side the computer plays
 */
void apply_panel_action(gomoku &game, app_window &win, panel_action action, game_mode mode, side computer)
{
    if (action == panel_action::UNDO)
    {
        game.undo();
        if (mode == game_mode::PVC && game.current_side() == computer)
            game.undo();
    }
    else if (action == panel_action::RESTART)
    {
        game.reset();
    }
    else if (action == panel_action::TOGGLE_FULLSCREEN)
    {
        toggle_fullscreen(win);
    }
}

/**
 * Plays the computer's move if it is the computer's turn.
 *
 * @param game     the game to play in
 * @param mode     the current game mode
 * @param computer the side the computer plays
 * @param settings how deep and how wide to search
 */
void handle_ai_turn(gomoku &game, game_mode mode, side computer, const ai_settings &settings)
{
    if (mode != game_mode::PVC || game.get_state() != game_state::PLAYING)
        return;
    if (game.current_side() != computer)
        return;

    search_result result = choose_placement(game.get_board(), computer, settings);
    if (result.found)
        game.place(result.best.row, result.best.col);
}

int main()
{
    gomoku game;

    panel_state state;
    state.mode = game_mode::PVP;
    state.show_last_move = true;
    state.sidebar.visible = true;
    state.sidebar.on_left = false;
    state.sidebar.width = 300;
    state.open.mode = true;
    state.open.game = true;
    state.open.view = true;
    state.open.moves = true;

    divider_drag drag;
    drag.active = false;
    drag.mouse_was_down = false;

    ai_settings ai = default_ai_settings();
    side computer = side::WHITE; // the player has Black and moves first

    app_window win = open_app_window("Gomoku", 1000, 700, 640, 420);
    setup_panel_style();
    result_overlay overlay = new_result_overlay();

    while (!quit_requested() && !window_close_requested(win.wnd))
    {
        process_events();
        sync_window_size(win);
        handle_shortcuts(win, state);
        update_result_overlay(overlay, game);

        int width = window_width(win.wnd);
        int height = window_height(win.wnd);

        screen_layout layout = compute_layout(width, height, state.sidebar);
        bool dragging = handle_divider_drag(drag, state.sidebar, layout, width);
        layout = compute_layout(width, height, state.sidebar);
        board_geometry geo = fit_board(layout.board_area);

        if (!dragging)
            handle_board_click(game, layout.board_area, geo);

        clear_screen(rgb_color(37, 37, 38));
        draw_game(game, layout.board_area, geo, state.show_last_move);
        draw_winning_line(game, geo, overlay.frames);
        draw_layout_chrome(layout, drag);

        panel_action action = draw_result_overlay(overlay, game, layout.board_area, state.mode, computer);
        if (state.sidebar.visible)
        {
            panel_action side_action = draw_control_panel(game, state, layout.sidebar);
            if (side_action != panel_action::NONE)
                action = side_action;
        }
        draw_activity_bar(state, layout.activity_bar);
        draw_interface();
        refresh_window(win.wnd, 60);

        apply_panel_action(game, win, action, state.mode, computer);

        // After the refresh, so the player's stone is on screen while the computer thinks.
        handle_ai_turn(game, state.mode, computer, ai);
    }

    close_all_windows();
    return 0;
}
