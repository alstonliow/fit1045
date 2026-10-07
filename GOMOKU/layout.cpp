#include "layout.h"

/** Extra pixels either side of the divider that still start a drag. */
const int DIVIDER_GRAB_SLACK = 3;

/**
 * Limits the sidebar width so it and the board area both fit.
 *
 * @param width     the requested sidebar width
 * @param win_width the window width in pixels
 * @return the width to use
 */
static int clamp_sidebar_width(int width, int win_width)
{
    int max_width = win_width - ACTIVITY_BAR_WIDTH - DIVIDER_WIDTH - MIN_BOARD_AREA_WIDTH;
    if (width > max_width)
        width = max_width;
    if (width < MIN_SIDEBAR_WIDTH)
        width = MIN_SIDEBAR_WIDTH;
    return width;
}

screen_layout compute_layout(int win_width, int win_height, const sidebar_settings &sidebar)
{
    screen_layout layout;
    int side_width = sidebar.visible ? clamp_sidebar_width(sidebar.width, win_width) : 0;
    int divider_width = sidebar.visible ? DIVIDER_WIDTH : 0;
    int board_width = win_width - ACTIVITY_BAR_WIDTH - side_width - divider_width;

    if (sidebar.on_left)
    {
        // | activity | sidebar | divider | board |
        layout.activity_bar = rectangle_from(0, 0, ACTIVITY_BAR_WIDTH, win_height);
        layout.sidebar = rectangle_from(ACTIVITY_BAR_WIDTH, 0, side_width, win_height);
        layout.divider = rectangle_from(ACTIVITY_BAR_WIDTH + side_width, 0, divider_width, win_height);
        layout.board_area = rectangle_from(win_width - board_width, 0, board_width, win_height);
    }
    else
    {
        // | board | divider | sidebar | activity |
        layout.board_area = rectangle_from(0, 0, board_width, win_height);
        layout.divider = rectangle_from(board_width, 0, divider_width, win_height);
        layout.sidebar = rectangle_from(board_width + divider_width, 0, side_width, win_height);
        layout.activity_bar = rectangle_from(win_width - ACTIVITY_BAR_WIDTH, 0, ACTIVITY_BAR_WIDTH, win_height);
    }
    return layout;
}

bool handle_divider_drag(divider_drag &drag, sidebar_settings &sidebar, const screen_layout &layout, int win_width)
{
    bool down = mouse_down(LEFT_BUTTON);
    bool pressed = down && !drag.mouse_was_down;
    bool was_active = drag.active;
    drag.mouse_was_down = down;

    if (pressed && sidebar.visible)
    {
        rectangle grab = rectangle_from(layout.divider.x - DIVIDER_GRAB_SLACK, layout.divider.y,
                                        layout.divider.width + 2 * DIVIDER_GRAB_SLACK, layout.divider.height);
        if (point_in_rectangle(mouse_position(), grab))
            drag.active = true;
    }

    if (drag.active && down)
    {
        double x = mouse_x();
        int width = sidebar.on_left ? (int)(x - ACTIVITY_BAR_WIDTH) : (int)(win_width - ACTIVITY_BAR_WIDTH - x);
        sidebar.width = clamp_sidebar_width(width, win_width);
    }
    else
    {
        drag.active = false;
    }

    return was_active || drag.active;
}

void draw_layout_chrome(const screen_layout &layout, const divider_drag &drag)
{
    rectangle a = layout.activity_bar;
    fill_rectangle(rgb_color(51, 51, 51), a.x, a.y, a.width, a.height);

    rectangle d = layout.divider;
    if (d.width > 0)
    {
        bool hot = drag.active || point_in_rectangle(mouse_position(), d);
        fill_rectangle(hot ? rgb_color(0, 122, 204) : rgb_color(60, 60, 60), d.x, d.y, d.width, d.height);
    }
}
