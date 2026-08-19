#include "splashkit.h"

const int PLAYER_RADIUS = 50;
const int PLAYER_SPEED = 3;

int main()
{
    int player_x = 640;
    int player_y = 360;

    open_window("Circle Moving", 1280, 720);

    while (!quit_requested())
    {
        clear_screen(COLOR_WHITE);
        fill_circle(COLOR_BLACK, player_x, player_y, PLAYER_RADIUS);
        refresh_screen(60);

        process_events();

        if (key_down(RIGHT_KEY))
        {
            player_x += PLAYER_SPEED;
        }

        if (key_down(LEFT_KEY))
        {
            player_x -= PLAYER_SPEED;
        }

        if (key_down(UP_KEY))
        {
            player_y -= PLAYER_SPEED;
        }

        if (key_down(DOWN_KEY))
        {
            player_y += PLAYER_SPEED;
        }
    }
}