#include "splashkit.h"
#include "utilities.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// three required states
enum game_state
{
    PLAYING,
    SHOWING_DETAILS,
    SHOWING_MENU
};

struct player_data
{
    point_2d pos{random_screen_point()};
    double radius{100};
    color clr{COLOR_BLACK};
    color light_clr{COLOR_LIGHT_GRAY};
};

// initialized in the state of PLAYING, random position, and not quit
struct game_data
{
    game_state state{PLAYING};
    player_data player{};
    bool quit{false};
};

game_data new_game()
{
    return {};
}

// draw in playong state
void draw_PLAYING(const game_data &game)
{
    clear_screen(COLOR_WHITE);
    fill_circle(game.player.clr, game.player.pos, game.player.radius);
    refresh_screen();
}

// draw in SHOWING_DETAILS state
void draw_details(const game_data &game)
{
    clear_screen(COLOR_LIGHT_BLUE);
    fill_circle(game.player.light_clr, game.player.pos, game.player.radius);
    fill_circle(COLOR_BLACK, game.player.pos, 2);
    draw_text(point_to_string(game.player.pos), COLOR_BLACK, game.player.pos.x - 10, game.player.pos.y - 10);
    refresh_screen();
}

// draw in SHOWING_MENU state
void draw_menu(const game_data &game)
{
    clear_screen(COLOR_LIGHT_GREEN);
    refresh_screen();
}

// draw game depends on cases
void draw_game(const game_data &game)
{
    switch (game.state)
    {
    case PLAYING:
        draw_PLAYING(game);
        break;
    case SHOWING_DETAILS:
        draw_details(game);
        break;
    case SHOWING_MENU:
        draw_menu(game);
        break;
    }
}

// update PLAYING state
void update_PLAYING(game_data &game)
{
    if (key_typed(SPACE_KEY))
    {
        game.player.pos = random_screen_point();
    }
    if (key_typed(NUM_1_KEY))
    {
        game.state = SHOWING_DETAILS;
    }
    if (key_typed(NUM_2_KEY))
    {
        game.state = SHOWING_MENU;
    }
}

// update details state
void update_details(game_data &game)
{
    if (key_typed(SPACE_KEY))
    {
        game.state = PLAYING;
    }
}

// update menu state
void update_menu(game_data &game)
{
    if (key_typed(SPACE_KEY))
    {
        game.state = PLAYING;
    }
    if (key_typed(Q_KEY))
    {
        game.quit = true;
    }
}

// update game state depends on cases
void update_game(game_data &game)
{
    switch (game.state)
    {
    case PLAYING:
        update_PLAYING(game);
        break;
    case SHOWING_DETAILS:
        update_details(game);
        break;
    case SHOWING_MENU:
        update_menu(game);
        break;
    }
}

int main()
{
    open_window("Game States", SCREEN_WIDTH, SCREEN_HEIGHT);

    game_data game = new_game();

    while (!game.quit && !quit_requested())
    {
        process_events();

        update_game(game);

        draw_game(game);
    }

    return 0;
}