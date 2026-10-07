#include "app_window.h"
#include <cstdint>

// SplashKit is built on SDL2 and libSplashKit exports these functions, but
// it does not ship SDL's headers, so declare just the ones used here.
struct SDL_Window;
extern "C"
{
    SDL_Window *SDL_GetWindowFromID(uint32_t id);
    const char *SDL_GetWindowTitle(SDL_Window *wnd);
    void SDL_SetWindowResizable(SDL_Window *wnd, int resizable);
    void SDL_SetWindowMinimumSize(SDL_Window *wnd, int min_w, int min_h);
    void SDL_GetWindowSize(SDL_Window *wnd, int *w, int *h);
}

/** Highest SDL window id to search; SplashKit opens very few windows. */
const uint32_t MAX_SDL_WINDOW_ID = 64;

/**
 * Finds the SDL window behind a SplashKit window by matching its title.
 *
 * @param wnd the SplashKit window
 * @return the SDL window, or nullptr if none has that title
 */
static SDL_Window *sdl_window_of(window wnd)
{
    string caption = window_caption(wnd);
    for (uint32_t id = 1; id <= MAX_SDL_WINDOW_ID; id++)
    {
        SDL_Window *sdl = SDL_GetWindowFromID(id);
        if (sdl != nullptr && caption == SDL_GetWindowTitle(sdl))
            return sdl;
    }
    return nullptr;
}

app_window open_app_window(const string &caption, int width, int height, int min_width, int min_height)
{
    app_window win;
    win.wnd = open_window(caption, width, height);
    win.windowed_width = width;
    win.windowed_height = height;

    SDL_Window *sdl = sdl_window_of(win.wnd);
    if (sdl != nullptr)
    {
        SDL_SetWindowResizable(sdl, 1);
        SDL_SetWindowMinimumSize(sdl, min_width, min_height);
    }
    return win;
}

void sync_window_size(app_window &win)
{
    SDL_Window *sdl = sdl_window_of(win.wnd);
    if (sdl == nullptr)
        return;

    int w, h;
    SDL_GetWindowSize(sdl, &w, &h);
    if (w != window_width(win.wnd) || h != window_height(win.wnd))
        resize_window(win.wnd, w, h);
}

void toggle_fullscreen(app_window &win)
{
    if (window_is_fullscreen(win.wnd))
    {
        window_toggle_fullscreen(win.wnd);
        // Otherwise the window keeps the screen size it had in fullscreen.
        resize_window(win.wnd, win.windowed_width, win.windowed_height);
    }
    else
    {
        win.windowed_width = window_width(win.wnd);
        win.windowed_height = window_height(win.wnd);
        window_toggle_fullscreen(win.wnd);
    }
}
