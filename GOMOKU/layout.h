#ifndef LAYOUT_H
#define LAYOUT_H

#include "splashkit.h"

/** Width in pixels of the strip that holds the sidebar toggle button. */
const int ACTIVITY_BAR_WIDTH = 36;

/** Width in pixels of the draggable bar between the board and the sidebar. */
const int DIVIDER_WIDTH = 6;

/** Narrowest the sidebar can be dragged to. */
const int MIN_SIDEBAR_WIDTH = 220;

/** Narrowest the board area can be squeezed to by the sidebar. */
const int MIN_BOARD_AREA_WIDTH = 300;

/** Where the sidebar is and how wide it is. */
struct sidebar_settings
{
    bool visible;
    bool on_left;
    int width;
};

/** The rectangles each part of the window occupies this frame. */
struct screen_layout
{
    rectangle board_area;
    rectangle sidebar;      // zero width when the sidebar is hidden
    rectangle divider;      // zero width when the sidebar is hidden
    rectangle activity_bar;
};

/** Whether the divider is being dragged, carried from frame to frame. */
struct divider_drag
{
    bool active;
    bool mouse_was_down;
};

/**
 * Splits the window into activity bar, sidebar, divider and board area.
 * The sidebar width is clamped so the board area keeps its minimum width.
 *
 * @param win_width  the window width in pixels
 * @param win_height the window height in pixels
 * @param sidebar    where the sidebar goes and how wide it should be
 * @return the rectangle for each part
 */
screen_layout compute_layout(int win_width, int win_height, const sidebar_settings &sidebar);

/**
 * Starts, continues or ends dragging the divider, changing the sidebar width.
 *
 * @param drag      the drag in progress, updated
 * @param sidebar   the sidebar whose width is changed while dragging
 * @param layout    this frame's layout, used to find the divider
 * @param win_width the window width in pixels
 * @return true if a drag was in progress this frame, so the mouse should
 *         not also be treated as a click on the board
 */
bool handle_divider_drag(divider_drag &drag, sidebar_settings &sidebar, const screen_layout &layout, int win_width);

/**
 * Draws the divider and activity bar backgrounds.
 *
 * @param layout this frame's layout
 * @param drag   the drag in progress, used to highlight the divider
 */
void draw_layout_chrome(const screen_layout &layout, const divider_drag &drag);

#endif
