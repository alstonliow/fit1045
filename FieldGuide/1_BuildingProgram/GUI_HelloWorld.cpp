#include "splashkit.h"

int main()
{
    open_window("My First GUI Program", 640, 480);

    clear_screen(COLOR_WHITE);
    draw_text("Hello World! - using SplashKit shapes:", COLOR_BLACK, 50, 50);

    // Draw the H
    fill_rectangle(COLOR_RED, 50, 100, 20, 100);
    fill_rectangle(COLOR_RED, 70, 140, 40, 20);
    fill_rectangle(COLOR_RED, 110, 100, 20, 100);

    // Draw the I
    fill_rectangle(COLOR_ORANGE, 150, 100, 20, 100);
   

    // Draw the W
    fill_triangle(COLOR_GREEN, 50, 250, 90, 370, 120, 250);
    fill_triangle(COLOR_GREEN, 90, 250, 120, 370, 160, 250);
    fill_triangle(COLOR_WHITE, 70, 250, 90, 310, 110, 250);
    fill_triangle(COLOR_WHITE, 100, 250, 120, 310, 140, 250);
    fill_rectangle(COLOR_WHITE, 70, 350, 80, 30);

    // Draw the O
    fill_ellipse(COLOR_BLUE, 170, 250, 80, 100);
    fill_ellipse(COLOR_WHITE, 190, 270, 40, 60);

    // Draw the R
    fill_triangle(COLOR_BLUE_VIOLET, 270, 250, 270, 350, 340, 350);
    fill_triangle(COLOR_WHITE, 252, 250, 252, 350, 320, 350);
    fill_ellipse(COLOR_BLUE_VIOLET, 252, 250, 80, 60);
    fill_ellipse(COLOR_WHITE, 270, 270, 40, 20);
    fill_rectangle(COLOR_WHITE, 252, 250, 20, 100);
    fill_rectangle(COLOR_BLUE_VIOLET, 270, 250, 20, 100);

    // Draw the L
    fill_rectangle(COLOR_PURPLE, 360, 250, 20, 100);
    fill_rectangle(COLOR_PURPLE, 380, 330, 40, 20);

    // Draw the D
    fill_ellipse(COLOR_MAGENTA, 420, 250, 100, 100);
    fill_ellipse(COLOR_WHITE, 440, 270, 60, 60);
    fill_rectangle(COLOR_WHITE, 420, 250, 30, 100);
    fill_rectangle(COLOR_MAGENTA, 450, 250, 20, 101);

    // Draw the !
    fill_rectangle(COLOR_PINK, 550, 250, 20, 60);
    fill_circle(COLOR_PINK, 560, 340, 10);

    refresh_screen();
    delay(5000);
}