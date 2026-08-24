#include "splashkit.h"
#include "splashkit-arrays.h"

// change DATA_SIZE to changing the number of bar
const int DATA_SIZE = 20;
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

// fill array random
void fill_array(fixed_array<int, DATA_SIZE> &data)
{
    for (int i = 0; i < DATA_SIZE; i++)
    {
        data[i] = rnd(0, screen_height()); // screen height more flexible
    }
}

// draw all the bar
void visuallize_array(const fixed_array<int, DATA_SIZE> &data)
{
    const color FILL_COLOR = COLOR_WHITE;

    // Split the window width evenly between the elements.
    double bar_width = (double)screen_width() / DATA_SIZE;

    clear_screen(COLOR_BLACK);

    for (int i = 0; i < DATA_SIZE; i++)
    {
        // Scale the value, then find the top-left corner of the bar.
        // Screen y grows downwards, so a taller bar starts higher up.
        double bar_height = (double)data[i];
        double x = i * bar_width; // actually (i+1)-1=i, the width of the pass one
        double y = screen_height() - bar_height;

        fill_rectangle(FILL_COLOR, x, y, bar_width, bar_height);
    }

    refresh_screen();
}

// insertion sort one time
void insertion_pass(fixed_array<int, DATA_SIZE> &data, int key_pos)
{
    int key = data[key_pos]; // current key
    int i = key_pos - 1;     // last position of sorted data

    while (i >= 0 && data[i] > key)
    {
        // all element before the key compare with key
        // if element > key, then move right
        data[i + 1] = data[i];
        i = i - 1; // move left to campare with key again
    }

    data[i + 1] = key;
}

// full insertion sort
void insertion_sort(fixed_array<int, DATA_SIZE> &data)
{
    for (int j = 1; j <= DATA_SIZE - 1; j++)
    {
        insertion_pass(data, j);
    }
}

int main()
{
    fixed_array<int, DATA_SIZE> data;

    open_window("Insertion Sort", WINDOW_WIDTH, WINDOW_HEIGHT);

    // must use after open window because screen_height()
    fill_array(data);

    while (!quit_requested())
    {
        process_events();
        visuallize_array(data);
    }

    return 0;
}