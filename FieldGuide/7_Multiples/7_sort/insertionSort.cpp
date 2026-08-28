#include "splashkit.h"
#include "splashkit-arrays.h"

// change DATA_SIZE to changing the number of bar
const int DATA_SIZE = 30;
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

// determine color of a single bar
// normal ~ white
// key ~ red
// compare bar ~ yellow

// difficult to write because
// need to think about how the insertion_sort() use it
// two gap between final use

// index:         the bar currently being drawn (0 .. DATA_SIZE-1)
// key_index:     the position key will be inserted into this step (i + 1)
// compare_index: the position currently being compared against key (i)
color get_color(int index, int key_index, int compare_index)
{
    if (index == key_index)
    {
        return COLOR_RED;
    }
    else if (index == compare_index)
    {
        return COLOR_YELLOW;
    }
    else
    {
        return COLOR_WHITE;
    }
}

// draw all the bar
void visualise_array(const fixed_array<int, DATA_SIZE> &data, int key_index, int compare_index)
{
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

        // using get_color to determine the color
        fill_rectangle(get_color(i, key_index, compare_index), x, y, bar_width, bar_height);
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

        // visualise with highlight
        visualise_array(data, key_pos, i);
        delay(50);
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
    insertion_sort(data);
    // data already sorted 100%

    while (!quit_requested())
    {
        process_events();
        // visualise_array(data);
        // useless because all animation in insertion_sort()
    }

    return 0;
}