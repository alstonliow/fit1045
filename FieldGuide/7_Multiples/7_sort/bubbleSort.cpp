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

// use many time
// determine the color of the bar to highlight the bar
color get_color(int index, int highlight_index1, int highlight_index2)
{
    // ternary operator
    // [expression to test] ? [if true, return this] : [otherwise, return this]
    // highlight with yellow
    return (index == highlight_index1 || index == highlight_index2) ? COLOR_YELLOW : COLOR_WHITE;
}

// draw bar
void visuallize_array(const fixed_array<int, DATA_SIZE> &data, int highlight_index1, int highlight_index2)
{
    // Split the window width evenly between the elements.
    double bar_width = (double)screen_width() / DATA_SIZE;

    clear_screen(COLOR_BLACK);

    for (int i = 0; i < length(data); i++)
    {
        // Scale the value, then find the top-left corner of the bar.
        // Screen y grows downwards, so a taller bar starts higher up.
        double bar_height = (double)data[i];
        double x = i * bar_width; // actually (i+1)-1=i, the width of the pass one
        double y = screen_height() - bar_height;

        fill_rectangle(get_color(i, highlight_index1, highlight_index2), x, y, bar_width, bar_height);
    }

    refresh_screen();
}

/**
 * Perform a single bubble sort pass over the first `range` elements,
 * swapping each out-of-order neighbouring pair. This bubbles the largest
 * value in that range to position range - 1. The array is redrawn after
 * every comparison so the sort can be watched as it happens.
 */
void bubble_sort_pass(fixed_array<int, DATA_SIZE> &data, int range)
{
    // swap of i and i+1, so need (range - 1)
    for (int i = 0; i < range - 1; i++)
    {
        // Out of order? Swap the pair using a temporary variable.
        if (data[i] > data[i + 1])
        {
            int temp = data[i];
            data[i] = data[i + 1];
            data[i + 1] = temp;
        }
        // here giving get_color() index1 and index2
        // when swap i and i + 1, highlight two bar
        visuallize_array(data, i, i + 1);
        delay(100); // slow things down so the change is visible
    }
}

/**
 * Sort the array into ascending order using bubble sort.
 * Each pass covers one fewer element, since every pass locks the largest
 * remaining value into place at the end of the range.
 */
void bubble_sort(fixed_array<int, DATA_SIZE> &data)
{
    for (int i = length(data); i > 1; i--)
    {
        bubble_sort_pass(data, i);
    }
}

int main()
{
    fixed_array<int, DATA_SIZE> data;

    open_window("Bubble Sort", WINDOW_WIDTH, WINDOW_HEIGHT);

    // must use after open window because screen_height()
    fill_array(data);

    // Run the sort - the animation happens inside bubble_sort_pass.
    bubble_sort(data);

    // Keep showing the finished result until the user closes the window.
    while (!quit_requested())
    {
        process_events();
        // -1 mean do not highlight anymore
        visuallize_array(data, -1, -1);
    }

    return 0;
}