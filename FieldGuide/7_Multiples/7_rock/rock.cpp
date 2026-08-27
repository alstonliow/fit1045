#include "splashkit.h"
#include "utilities.h"
#include "splashkit-arrays.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int PLAYER_SPEED = 5;

const int INIT_ROCK_COUNT = 3;
const int MAX_ROCK_COUNT = 100;

struct entity
{
    bool enabled = true;
    point_2d pos;
    double size;
    bitmap bmp;
    int speed;
    color clr;
    // sprite spr{};
};

// rocks is entity
struct rock_data
{
    entity ent;
    bool mark_for_remove = false;
};

// player is entity
struct player_data
{
    entity ent;
};

struct game_data
{
    dynamic_array<rock_data> rocks;
    player_data player;
    int score;
    int lives = 3;
    bitmap background;
};

// initial the game
// contains init_rocks, init_player and new rocks

// new rock, for one rock
// here can setting the difficulty of the game
rock_data new_rock(bitmap rock_bmp)
{
    rock_data rock;

    rock.ent.size = rnd(30, 100);
    rock.ent.pos.x = rnd(0, SCREEN_WIDTH - rock.ent.size);
    rock.ent.pos.y = -rock.ent.size;
    rock.ent.speed = rnd(1, 5);
    rock.ent.clr = COLOR_BROWN;
    rock.ent.bmp = rock_bmp;

    return rock;
}

// init rocks, for many rocks
void init_rocks(dynamic_array<rock_data> &rocks, bitmap rock_bmp)
{
    for (int i = 0; i < INIT_ROCK_COUNT; i++)
    {
        add(rocks, new_rock(rock_bmp));
    }
}

// new player data
player_data new_player(bitmap player_bmp)
{
    player_data player;

    player.ent.size = 30;
    player.ent.pos.x = (SCREEN_WIDTH / 2) - (player.ent.size / 2); // player at middle
    player.ent.pos.y = SCREEN_HEIGHT - player.ent.size;            // player at bottom
    player.ent.speed = PLAYER_SPEED;
    player.ent.clr = COLOR_BLUE;
    player.ent.bmp = player_bmp;

    return player;
}

// init game, combine rock and player initial data
void init_game(game_data &game, bitmap rock_bmp, bitmap player_bmp)
{
    init_rocks(game.rocks, rock_bmp);
    game.player = new_player(player_bmp);
}

// draw game

void draw_entity(entity &ent)
{
    if (!ent.enabled)
    {
        return;
    }

    double bmp_w = bitmap_width(ent.bmp);
    double bmp_h = bitmap_height(ent.bmp);

    // scale the bitmap down to the entity size
    double scale_x = ent.size / bmp_w;
    double scale_y = ent.size / bmp_h;

    // splashkit scales a bitmap around centre
    // setting pos stays the top-left corner of the entity.
    double draw_x = ent.pos.x - (bmp_w - ent.size) / 2;
    double draw_y = ent.pos.y - (bmp_h - ent.size) / 2;

    draw_bitmap(ent.bmp, draw_x, draw_y, option_scale_bmp(scale_x, scale_y));
}

// using bitmap
void draw_background();

// draw game
void draw_game(game_data &game)
{
    clear_screen(COLOR_WHITE);

    draw_entity(game.player.ent);

    for (int i = 0; i < length(game.rocks); i++)
    {
        draw_entity(game.rocks[i].ent);
    }

    // draw the remaining lives of player on screen
    draw_text("Lives: " + to_string(game.lives), COLOR_BLACK, 10, 10);
    draw_text("Scores: " + to_string(game.score), COLOR_BLACK, 10, 20);

    refresh_screen(60);
}

// update game part

// move with key
void move_with_key(entity &ent)
{
    if (key_down(RIGHT_KEY))
    {
        ent.pos.x += ent.speed;
    }
    if (key_down(LEFT_KEY))
    {
        ent.pos.x -= ent.speed;
    }

    if ((ent.pos.x + ent.size) > SCREEN_WIDTH)
    {
        ent.pos.x = SCREEN_WIDTH - ent.size;
    }
    if (ent.pos.x < 0)
    {
        ent.pos.x = 0;
    }
}

// update the position of rock with its speed with 60fps
void update_falling(entity &ent)
{
    ent.pos.y += ent.speed;
}

// update the position with horizontal
void update_hori(entity &ent)
{
    ent.pos.x += ent.speed;
}

// check if out of screen
bool out_of_screen(const entity &ent)
{
    return ent.pos.y > SCREEN_HEIGHT;
}

// check it when collide
bool entities_collide(const entity &ent1, const entity &ent2)
{
    if (!ent1.enabled || !ent2.enabled)
    {
        return false;
    }

    double radius_1 = ent1.size / 2;
    double radius_2 = ent2.size / 2;

    double circe_x_1 = ent1.pos.x + radius_1;
    double circle_x_2 = ent1.pos.y + radius_1;
    double circle_y_1 = ent2.pos.x + radius_2;
    double circle_y_2 = ent2.pos.y + radius_2;

    return circles_intersect(circe_x_1, circle_x_2, radius_1, circle_y_1, circle_y_2, radius_2);
}

// randomly decide whether to generate a new entity
bool generate_entity()
{
    return rnd(1, 100) <= 2; // 2 % to generate a new entity
}

// update game, combine all update function
void update_game(game_data &game, bitmap rock_bmp)
{
    move_with_key(game.player.ent);

    // loop the rocks array
    for (int i = 0; i < length(game.rocks); i++)
    {
        update_falling(game.rocks[i].ent);

        if (out_of_screen(game.rocks[i].ent))
        {
            game.rocks[i].mark_for_remove = true;
            game.score++;
        }
        if (entities_collide(game.rocks[i].ent, game.player.ent))
        {
            game.rocks[i].mark_for_remove = true;
            game.lives--;
        }
    }

    // remove the rock has been marked from backward
    for (int i = length(game.rocks) - 1; i >= 0; i--)
    {
        if (game.rocks[i].mark_for_remove)
        {
            remove(game.rocks, i);
        }
    }

    if (generate_entity() && length(game.rocks) < MAX_ROCK_COUNT)
    {
        add(game.rocks, new_rock(rock_bmp));
    }
}

int main()
{
    open_window("Rock Dodge", SCREEN_WIDTH, SCREEN_HEIGHT);

    bitmap player_bmp = load_bitmap("player", "player.png");
    bitmap rock_bmp = load_bitmap("rock", "rock.png");

    game_data game;
    init_game(game, rock_bmp, player_bmp);

    while (!quit_requested() && game.lives > 0)
    {
        process_events();
        update_game(game, rock_bmp);
        draw_game(game);
    }

    return 0;
}