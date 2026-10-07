#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include "splashkit.h"

/**
 * A SplashKit window that the user can resize and switch to fullscreen.
 *
 * SplashKit opens fixed-size windows and ignores resize events, so this turns
 * on SDL's resizable flag and, each frame, resizes SplashKit's drawing surface
 * to match the real window size.
 */
struct app_window
{
    window wnd;
    int windowed_width;  // size to restore when leaving fullscreen
    int windowed_height;
};

/**
 * Opens a resizable window.
 *
 * @param caption    the window title, must be unique among open windows
 * @param width      the starting width in pixels
 * @param height     the starting height in pixels
 * @param min_width  the smallest width the user can drag the window to
 * @param min_height the smallest height the user can drag the window to
 * @return the opened window
 */
app_window open_app_window(const string &caption, int width, int height, int min_width, int min_height);

/**
 * Resizes SplashKit's drawing surface if the user has resized the window.
 * Call once per frame, after process_events().
 *
 * @param win the window to check
 */
void sync_window_size(app_window &win);

/**
 * Switches between fullscreen and the previous windowed size.
 *
 * @param win the window to switch
 */
void toggle_fullscreen(app_window &win);

#endif
