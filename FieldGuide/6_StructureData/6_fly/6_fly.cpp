#include "splashkit.h"
#include "utilities.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SPEED = 3;

struct entity
{
    bool enabled{1};

    point_2d pos{};
    double radius{};

    bitmap bmp{};
    int speed{SPEED};
};

struct timespan
{
    long start{};
    long duration{};
};

struct spider_data
{
    entity ent{};
};

struct fly_data
{
    entity ent{};
    timespan caught_interval{};
};

struct game_data
{
    spider_data spider{};
    fly_data fly{};
    bitmap background{};
    int score{0};
};

spider_data new_spider(bitmap spider_bmp)
{
    return {true, {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, 30, spider_bmp};
}

fly_data new_fly(long current_time, bitmap fly_bmp)
{
    fly_data fly{};

    fly.ent = {
        false,
        {(double)rnd(SCREEN_WIDTH), (double)rnd(SCREEN_HEIGHT)},
        15,
        fly_bmp};

    fly.caught_interval = {current_time + 1000 + rnd(2000), 2000 + rnd(5000)};

    return fly;
}

void draw_entity(const entity &ent)
{
    // exit if disabled
    // early return to exit the function
    if (!ent.enabled)
    {
        return;
    }

    draw_bitmap(ent.bmp, ent.pos.x - ent.radius, ent.pos.y - ent.radius);
}

void draw_game(const game_data &game)
{
    clear_screen(COLOR_WHITE);

    // Draw background
    draw_bitmap(game.background, 0, 0);

    // Draw spider
    draw_entity(game.spider.ent);

    // Draw fly
    draw_entity(game.fly.ent);

    // draw the score
    draw_text("Score: " + to_string(game.score), COLOR_ANTIQUE_WHITE, 0, 10);

    refresh_screen();
}

void move_with_key(entity &ent)
{
    if (key_down(RIGHT_KEY) || key_down(D_KEY))
    {
        ent.pos.x += ent.speed;
    }
    if (key_down(LEFT_KEY) || key_down(A_KEY))
    {
        ent.pos.x -= ent.speed;
    }
    if (key_down(DOWN_KEY) || key_down(S_KEY))
    {
        ent.pos.y += ent.speed;
    }
    if (key_down(UP_KEY) || key_down(W_KEY))
    {
        ent.pos.y -= ent.speed;
    }

    // check right
    if (ent.pos.x + ent.radius > SCREEN_WIDTH)
    {
        ent.pos.x = SCREEN_WIDTH - 2 * ent.radius;
    }
    // check left
    if (ent.pos.x - ent.radius < 0)
    {
        ent.pos.x = 2 * ent.radius;
    }
    // check down
    if (ent.pos.y + ent.radius > SCREEN_HEIGHT)
    {
        ent.pos.y = SCREEN_HEIGHT - 2 * ent.radius;
    }
    // check up
    if (ent.pos.y - ent.radius < 0)
    {
        ent.pos.y = 2 * ent.radius;
    }
}

// Time span function start

// full within_timespan span.start <= time < (span.start + span.duration)
bool within_timepsan(const timespan &span, long time)
{
    return (time >= span.start) && (time < (span.start + span.duration));
}

bool after_timespan(const timespan &span, long time)
{
    return time >= (span.start + span.duration);
}

// overloading : use a easier version of a function to call a full version
bool within_timespan(const timespan &span)
{
    return within_timepsan(span, current_ticks());
}

// Time span function end

void update_fly(fly_data &fly, long current_time)
{
    fly.ent.enabled = within_timepsan(fly.caught_interval, current_time);

    if (after_timespan(fly.caught_interval, current_time))
    {
        fly = new_fly(current_time, fly.ent.bmp);
    }
}

// when spider catch fly
bool entities_collide(const entity &ent1, const entity &ent2)
{
    return ent1.enabled && ent2.enabled && circles_intersect(ent1.pos.x, ent1.pos.y, ent1.radius, ent2.pos.x, ent2.pos.y, ent2.radius);
}

void update_game(game_data &game, long current_time)
{
    move_with_key(game.spider.ent);

    // if collided, score +1
    if (entities_collide(game.spider.ent, game.fly.ent))
    {
        game.fly = new_fly(current_time, game.fly.ent.bmp);
        game.score++;
    }

    update_fly(game.fly, current_time);
}

int main()
{
    open_window("Fly Catch", SCREEN_WIDTH, SCREEN_HEIGHT);

    bitmap spider_bmp = load_bitmap("spider", "spider.png");
    bitmap fly_bmp = load_bitmap("fly", "fly.png");
    bitmap background_bmp = load_bitmap("background", "background.png");

    game_data game{};
    game.spider = new_spider(spider_bmp);
    game.fly = new_fly(current_ticks(), fly_bmp);
    game.background = background_bmp;

    // The event loop
    while (!quit_requested())
    {
        process_events();

        update_game(game, current_ticks());

        draw_game(game);
    }
}