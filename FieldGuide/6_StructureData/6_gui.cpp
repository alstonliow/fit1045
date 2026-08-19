#include "splashkit.h"
#include "utilities.h"

const int MAX_TARGET_RADIUS = 300;
const int MIN_TARGET_RADIUS = 10;

struct target_data
{
    double x{400};
    double y{300};
    double radius{75};
};

struct reaction_game_data
{
    target_data target{};
    int hits{0};
};

target_data new_target(double x, double y, double radius)
{
    return {x, y, radius};
}

target_data random_target()
{
    int radius = rnd(MAX_TARGET_RADIUS - MIN_TARGET_RADIUS) + MIN_TARGET_RADIUS;

    return new_target(
        rnd(radius, screen_width() - radius),
        rnd(radius, screen_height() - radius),
        radius);
}

void draw_target(target_data target)
{
    fill_circle(COLOR_LIGHT_BLUE, target.x, target.y, target.radius);
}

bool mouse_over_target(target_data target)
{
    return point_in_circle(mouse_x(), mouse_y(), target.x, target.y, target.radius);
}

reaction_game_data new_reaction_game()
{
    return {random_target(), 0};
}

int game_avr_time(reaction_game_data game)
{
    if (game.hits == 0)
    {
        return current_ticks();
    }
    else
    {
        return current_ticks() / game.hits;
    }
}

void draw_game(reaction_game_data game)
{
    clear_screen(COLOR_WHITE);
    draw_text("Hits: " + to_string(game.hits), COLOR_BLACK, 0, 0);
    draw_text("Average time: " + to_string(game_avr_time(game)), COLOR_BLACK, 0, 10);
    draw_target(game.target);
    refresh_screen();
}

int main()
{
    open_window("Reaction Timer", 800, 600);

    reaction_game_data game = new_reaction_game();

    while (!quit_requested())
    {
        process_events();

        if (mouse_clicked(LEFT_BUTTON) && mouse_over_target(game.target))
        {
            game.target = random_target();
            game.hits++;
        }
        draw_game(game);
    }

    return 0;
}