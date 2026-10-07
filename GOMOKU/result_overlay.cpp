#include "result_overlay.h"

/** Frames to wait after the winning move, so the winning line is seen first. */
const int DELAY_FRAMES = 24;

/** Frames for the card to slide in and the background to darken. */
const int FADE_FRAMES = 18;

/** How far below its final position the card starts, in pixels. */
const int SLIDE_DISTANCE = 30;

/** Card size and spacing, in pixels. */
const int CARD_WIDTH = 380;
const int CARD_HEIGHT = 210;
const int CARD_RADIUS = 16;
const int CARD_PADDING = 24;
const int BUTTON_GAP = 12;
const int BUTTON_HEIGHT = 34;

/** Text sizes when the title font is loaded. */
const int TITLE_SIZE = 36;
const int SUBTITLE_SIZE = 16;

/** Width of one character in SplashKit's default font. */
const int DEFAULT_CHAR_PX = 8;

/**
 * Gets the card's background colour.
 *
 * @return a dark grey matching the sidebar
 */
static color card_colour()
{
    return rgb_color(32, 33, 36);
}

/**
 * Gets the accent colour for the result.
 *
 * @param state how the game ended
 * @return gold for a win, grey for a draw
 */
static color accent_colour(game_state state)
{
    return (state == game_state::DRAW) ? rgb_color(140, 140, 140) : rgb_color(232, 183, 64);
}

result_overlay new_result_overlay()
{
    result_overlay overlay;
    overlay.frames = 0;
    overlay.dismissed = false;
    overlay.title_font = load_font("overlay", "Poppins-SemiBold.ttf");
    overlay.font_loaded = has_font("overlay");
    return overlay;
}

void update_result_overlay(result_overlay &overlay, const gomoku &game)
{
    if (game.get_state() == game_state::PLAYING)
    {
        overlay.frames = 0;
        overlay.dismissed = false;
    }
    else
    {
        overlay.frames++;
    }
}

/**
 * Gets the large heading for the result.
 *
 * @param game     the finished game
 * @param mode     the game mode
 * @param computer the side the computer plays
 * @return e.g. "Black wins!", "You win!" or "Draw"
 */
static string result_title(const gomoku &game, game_mode mode, side computer)
{
    game_state state = game.get_state();
    if (state == game_state::DRAW)
        return "Draw";

    side winner = (state == game_state::BLACK_WIN) ? side::BLACK : side::WHITE;
    if (mode == game_mode::PVC)
        return (winner == computer) ? "Computer wins" : "You win!";
    return (winner == side::BLACK) ? "Black wins!" : "White wins!";
}

/**
 * Gets the line under the heading.
 *
 * @param game the finished game
 * @return how the game ended and after how many moves
 */
static string result_subtitle(const gomoku &game)
{
    if (game.get_state() == game_state::DRAW)
        return "The board is full after " + to_string(game.placement_count()) + " moves";
    return "Five in a row after " + to_string(game.placement_count()) + " moves";
}

/**
 * Draws text centred on a point, using the overlay font if it loaded.
 *
 * @param overlay the overlay holding the font
 * @param text    the text to draw
 * @param clr     the text colour
 * @param size    the font size
 * @param centre  the x position to centre on
 * @param y       the top of the text
 */
static void draw_centred_text(const result_overlay &overlay, const string &text, color clr, int size,
                              double centre, double y)
{
    if (overlay.font_loaded)
    {
        int width = text_width(text, overlay.title_font, size);
        draw_text(text, clr, overlay.title_font, size, centre - width / 2.0, y);
    }
    else
    {
        draw_text(text, clr, centre - DEFAULT_CHAR_PX * (int)text.length() / 2.0, y);
    }
}

/**
 * Fills a rectangle with rounded corners. The colour should be opaque:
 * the pieces overlap, so a see-through colour would show darker spots.
 *
 * @param clr    the fill colour
 * @param x      the left edge
 * @param y      the top edge
 * @param width  the width
 * @param height the height
 * @param radius the corner radius
 */
static void fill_rounded_rectangle(color clr, double x, double y, double width, double height, double radius)
{
    fill_rectangle(clr, x + radius, y, width - 2 * radius, height);
    fill_rectangle(clr, x, y + radius, radius, height - 2 * radius);
    fill_rectangle(clr, x + width - radius, y + radius, radius, height - 2 * radius);
    fill_circle(clr, x + radius, y + radius, radius);
    fill_circle(clr, x + width - radius, y + radius, radius);
    fill_circle(clr, x + radius, y + height - radius, radius);
    fill_circle(clr, x + width - radius, y + height - radius, radius);
}

/**
 * Draws a stone with a soft highlight, so it looks round.
 *
 * @param s      whose stone
 * @param x      the centre x
 * @param y      the centre y
 * @param radius the stone radius
 */
static void draw_shiny_stone(side s, double x, double y, double radius)
{
    if (s == side::BLACK)
    {
        fill_circle(rgb_color(20, 20, 20), x, y, radius);
        fill_circle(rgb_color(70, 70, 70), x - radius * 0.3, y - radius * 0.3, radius * 0.25);
    }
    else
    {
        fill_circle(rgb_color(225, 225, 225), x, y, radius);
        fill_circle(COLOR_WHITE, x - radius * 0.3, y - radius * 0.3, radius * 0.35);
    }
}

/**
 * Draws the badge on the card's top edge: the winner's stone in a ring,
 * or one stone of each colour for a draw.
 *
 * @param state how the game ended
 * @param x     the badge centre x
 * @param y     the badge centre y
 */
static void draw_badge(game_state state, double x, double y)
{
    color accent = accent_colour(state);

    if (state == game_state::DRAW)
    {
        fill_circle(accent, x - 18, y, 30);
        fill_circle(accent, x + 18, y, 30);
        fill_circle(card_colour(), x - 18, y, 27);
        fill_circle(card_colour(), x + 18, y, 27);
        draw_shiny_stone(side::BLACK, x - 18, y, 23);
        draw_shiny_stone(side::WHITE, x + 18, y, 23);
        return;
    }

    side winner = (state == game_state::BLACK_WIN) ? side::BLACK : side::WHITE;
    fill_circle(accent, x, y, 38);
    fill_circle(card_colour(), x, y, 34);
    draw_shiny_stone(winner, x, y, 29);
}

/**
 * Gets how far the entrance animation has got, slowing towards the end.
 *
 * @param frames frames since the game ended
 * @return 0 before the card appears, rising to 1 when it has settled
 */
static double entrance_progress(int frames)
{
    int shown = frames - DELAY_FRAMES;
    if (shown <= 0)
        return 0;
    if (shown >= FADE_FRAMES)
        return 1;

    double t = (double)shown / FADE_FRAMES;
    return 1 - (1 - t) * (1 - t); // ease-out
}

panel_action draw_result_overlay(result_overlay &overlay, const gomoku &game, const rectangle &area,
                                 game_mode mode, side computer)
{
    panel_action action = panel_action::NONE;
    game_state state = game.get_state();
    double progress = entrance_progress(overlay.frames);

    if (state == game_state::PLAYING || progress == 0)
        return action;

    double centre_x = area.x + area.width / 2;

    // After "View board", offer a small button to bring the card back.
    if (overlay.dismissed)
    {
        if (button("Show result", rectangle_from(centre_x - 70, area.y + 12, 140, 30)))
            overlay.dismissed = false;
        return action;
    }

    // Darken the board behind the card.
    fill_rectangle(rgba_color(0, 0, 0, (int)(150 * progress)), area.x, area.y, area.width, area.height);

    double width = CARD_WIDTH;
    if (width > area.width - 32)
        width = area.width - 32;
    double x = centre_x - width / 2;
    double y = area.y + (area.height - CARD_HEIGHT) / 2 + SLIDE_DISTANCE * (1 - progress);

    // A thin accent border, then the card.
    color accent = accent_colour(state);
    fill_rounded_rectangle(accent, x - 2, y - 2, width + 4, CARD_HEIGHT + 4, CARD_RADIUS + 2);
    fill_rounded_rectangle(card_colour(), x, y, width, CARD_HEIGHT, CARD_RADIUS);
    draw_badge(state, centre_x, y);

    draw_centred_text(overlay, result_title(game, mode, computer), COLOR_WHITE, TITLE_SIZE, centre_x, y + 48);
    draw_centred_text(overlay, result_subtitle(game), rgb_color(170, 170, 170), SUBTITLE_SIZE, centre_x, y + 98);
    draw_line(rgb_color(60, 60, 60), x + CARD_PADDING, y + 134, x + width - CARD_PADDING, y + 134);

    // Three buttons in a row along the bottom.
    double button_width = (width - 2 * CARD_PADDING - 2 * BUTTON_GAP) / 3;
    double button_y = y + 152;
    double left = x + CARD_PADDING;

    if (button("Play again", rectangle_from(left, button_y, button_width, BUTTON_HEIGHT)))
        action = panel_action::RESTART;
    if (button("Undo", rectangle_from(left + button_width + BUTTON_GAP, button_y, button_width, BUTTON_HEIGHT)))
        action = panel_action::UNDO;
    if (button("View board", rectangle_from(left + 2 * (button_width + BUTTON_GAP), button_y, button_width, BUTTON_HEIGHT)))
        overlay.dismissed = true;

    return action;
}
