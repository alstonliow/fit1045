#include "splashkit.h"

int main()
{
    open_window("House Drawing by Alston", 800, 600);

    clear_screen(COLOR_WHITE);
    fill_ellipse(COLOR_BRIGHT_GREEN, 0, 400, 800, 400);
    fill_rectangle(COLOR_GRAY, 250, 300, 300, 200);
    fill_triangle(COLOR_DARK_KHAKI, 220, 300, 400, 150, 580, 300);
    fill_rectangle(COLOR_BLACK, 375, 400, 50, 100);

    refresh_screen();

    delay(50000);

    return 0;
}