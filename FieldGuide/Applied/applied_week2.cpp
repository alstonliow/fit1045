#include "splashkit.h"

int main()
{
    // open window with name "shapes within shapes" with length 750 and height 550
    open_window("Shapes within shapes", 750, 550);

    // window background with black
    clear_screen(COLOR_BLACK);

    // first point position is (350, 100) and length 300 and h 300
    fill_rectangle(COLOR_WHITE, 350, 100, 300, 300);

    // centre of (500, 250) and raidus 120
    fill_circle(COLOR_GREEN, 500, 250, 120);

    // centre is (420, 180) and length 160 , height 100
    fill_ellipse(COLOR_BLUE, 420, 180, 160, 100);

    // position of centre of circle is (500, 240) and radius with 40
    fill_circle(COLOR_PINK, 500, 240, 40);

    // three point of triangle x and y
    fill_triangle(COLOR_RED, 500, 240, 470, 260, 530, 260);

    // allow the shape show in window
    refresh_screen();

    // prevent window close
    delay(10000);
}