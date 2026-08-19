#include "splashkit.h"
#include "utilities.h"

const int CIRCLE_RADIUS = 100;

// Check if the target has been hit, when hit, return true
bool target_hit(double x, double y, double radius)
{
    return point_in_circle(mouse_x(), mouse_y(), x, y, radius) && mouse_clicked(LEFT_BUTTON);
}

// Give target random position
void random_target_position(int &target_x, int &target_y, int window_x, int window_y)
{
    target_x = rnd(CIRCLE_RADIUS, window_x - CIRCLE_RADIUS);
    target_y = rnd(CIRCLE_RADIUS, window_y - CIRCLE_RADIUS);
}

// change direction of velocity when hit boundary
void change_direction(int target_x, int target_y, int window_x, int window_y, int &speed_x, int &speed_y)
{
    if ((target_x > (window_x - CIRCLE_RADIUS) && speed_x > 0) || (target_x < CIRCLE_RADIUS && speed_x < 0))
    {
        speed_x = -speed_x;
    }
    if ((target_y > (window_y - CIRCLE_RADIUS) && speed_y > 0) || (target_y < (CIRCLE_RADIUS + 100) && speed_y < 0))
    {
        speed_y = -speed_y;
    }
}

// Draw a progress bar
void draw_progress(double bar_x, double bar_y, double bar_width, double bar_height, double percent)
{
    // fill the black background of the progress bar
    fill_rectangle(COLOR_BLACK, bar_x, bar_y, bar_width, bar_height);

    // setting the data of the green progress bar
    double progress_length = bar_width * 0.999;
    double progress_height = bar_height * 0.96;
    double progress_x = bar_x + (bar_width - progress_length) / 2;
    double progress_y = bar_y + (bar_height - progress_height) / 2;

    // fill lime green progress bar with it ratio
    fill_rectangle(COLOR_LIME_GREEN, progress_x, progress_y, progress_length * percent, progress_height);
}

// renew target coordinate
void renew_target_coordinate(int &target_x, int &target_y, int &speed_x, int &speed_y, int window_x, int window_y)
{
    // renew the position with current speed (x, y)
    // moving toward direction x and y according to the speed
    target_x += speed_x;
    target_y += speed_y;

    // check if hit boundary
    change_direction(target_x, target_y, window_x, window_y, speed_x, speed_y);
}

// update game
void update_game(int &target_x, int &target_y, int &speed_x, int &speed_y,
                 int window_x, int window_y, int &hit_count)
{
    // renew target position
    renew_target_coordinate(target_x, target_y, speed_x, speed_y, window_x, window_y);

    // if the target hit, hit_count increase one, renew target position
    if (target_hit(target_x, target_y, CIRCLE_RADIUS))
    {
        hit_count++;
        random_target_position(target_x, target_y, window_x, window_y);
    }
}

// Draw the target circle
void draw_target(int target_x, int target_y)
{
    fill_circle(COLOR_LIME, target_x, target_y, CIRCLE_RADIUS);
}

// Draw the progress bar with ratio
void draw_hit_progress(int window_x, int window_y, int hit_count, int target_score)
{
    // setting the position and size of the progress bar, at the top of screen
    double rect_x = 10, rect_y = 10;
    double rect_length = window_x - (rect_x * 2);
    double rect_height = (window_y - (rect_y * 2)) / 10;

    // draw the progress bar with ratio, ratio = hit_count / target_score
    draw_progress(rect_x, rect_y, rect_length, rect_height, (double)hit_count / (double)target_score);
}

// full click game progress
void play_click_game(int &target_x, int &target_y, int &speed_x, int &speed_y,
                     int window_x, int window_y, int &hit_count, int target_score)
{
    // update the game status, about target
    update_game(target_x, target_y, speed_x, speed_y, window_x, window_y, hit_count);

    // draw target and progress bar
    draw_target(target_x, target_y);
    draw_hit_progress(window_x, window_y, hit_count, target_score);
}

int main()
{
    // initialised the speed, window, target_score, hit_count = 0, target position
    int speed_x = 1, speed_y = 1;
    int window_x = 1280, window_y = 720;
    int target_score{}, hit_count = 0;
    int target_x{}, target_y{};

    write_line("Welcome to target click.");

    // Ask about the target score from user
    target_score = read_integer("What is your target score: ", 1, 1000);
    write_line("Click " + to_string(target_score) + " to end the game.");

    open_window("Click Game", window_x, window_y);

    // initialised the target position with random
    random_target_position(target_x, target_y, window_x, window_y);

    // game loop, continue update when no any quit requested
    do
    {
        clear_screen(COLOR_WHITE);

        // all game process
        play_click_game(target_x, target_y, speed_x, speed_y, window_x, window_y, hit_count, target_score);

        refresh_screen(144);

        process_events();

    } while ((hit_count < target_score) && !quit_requested());

    close_window("Click Game");
}
