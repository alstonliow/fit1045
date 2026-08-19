#include "splashkit.h"
#include "splashkit-arrays.h"

const int DATA_SIZE = 10;
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

void visuallize_array(const fixed_array<int, DATA_SIZE> &data)
{
    const int MAX_VALUE = 10;
    const color FILL_COLOR = COLOR_BLUE;

    double bar_width = (double)WINDOW_WIDTH / DATA_SIZE;

    clear_screen(COLOR_WHITE);

    for (int i = 0; i < length(data); i++)
    {
        double bar_height = (double)data[i] * WINDOW_HEIGHT / MAX_VALUE;
        double x = i * bar_width;
        double y = WINDOW_HEIGHT - bar_height;

        fill_rectangle(FILL_COLOR, x, y, bar_width, bar_height);
    }

    refresh_screen();
}

void bubble_sort_pass(fixed_array<int, DATA_SIZE> &data, int range)
{
    for (int i = 0; i < range - 1; i++)
    {
        if (data[i] > data[i + 1])
        {
            int temp = data[i];
            data[i] = data[i + 1];
            data[i + 1] = temp;
        }
        visuallize_array(data);
        delay(50);
    }
}

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

    data[0] = 2;
    data[1] = 7;
    data[2] = 9;
    data[3] = 2;
    data[4] = 7;
    data[5] = 3;
    data[6] = 10;
    data[7] = 3;
    data[8] = 2;
    data[9] = 1;

    open_window("Bubble Sort", WINDOW_WIDTH, WINDOW_HEIGHT);

    bubble_sort(data);

    while (!quit_requested())
    {
        process_events();
        visuallize_array(data);
    }

    return 0;
}