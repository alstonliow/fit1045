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

/**
 * Determine the color of a single bar during a merge step.
 *
 *   COLOR_YELLOW -> the bar at position i (left pointer, currently
 *                    being compared)
 *   COLOR_RED    -> the bar at position j (right pointer, currently
 *                    being compared)
 *   COLOR_BLUE   -> a bar inside the left half [left, mid], not
 *                    currently pointed to by i
 *   COLOR_GREEN  -> a bar inside the right half [mid+1, right], not
 *                    currently pointed to by j
 *   COLOR_WHITE  -> a bar outside the current [left, right] range
 *                    (already merged, or not yet reached by this
 *                    recursive call)
 *
 * @param index the bar currently being drawn (0 .. DATA_SIZE-1)
 * @param left  start of the range currently being merged
 * @param mid   the boundary between the left and right halves within
 *              [left, right] (left half is [left, mid], right half
 *              is [mid+1, right])
 * @param right end of the range currently being merged
 * @param i     the left-half pointer used in the merge comparison
 * @param j     the right-half pointer used in the merge comparison
 * @return the color this bar should be drawn with
 */
color get_color(int index, int left, int mid, int right, int i, int j)
{
    if (index == i)
    {
        return COLOR_YELLOW;
    }
    else if (index == j)
    {
        return COLOR_RED;
    }
    else if (index >= left && index <= mid)
    {
        return COLOR_BLUE;
    }
    else if (index > mid && index <= right)
    {
        return COLOR_GREEN;
    }
    else
    {
        return COLOR_WHITE;
    }
}

// visualise, draw the bar
void visualise_array(const fixed_array<int, DATA_SIZE> &data, int left, int mid, int right, int i, int j)
{
    double bar_width = (double)screen_width() / length(data);
    clear_screen(COLOR_BLACK);

    for (int k = 0; k < length(data); k++)
    {
        // Scale the value, then find the top-left corner of the bar.
        // Screen y grows downwards, so a taller bar starts higher up.
        double bar_height = (double)data[k];
        double x = k * bar_width;
        double y = (double)screen_height() - bar_height;

        // using get_color to determine the color
        fill_rectangle(get_color(k, left, mid, right, i, j), x, y, bar_width, bar_height);
    }

    refresh_screen();
}

void merge(fixed_array<int, DATA_SIZE> &data, int left, int mid, int right)
{
    dynamic_array<int> temp;
    int i = left;
    int j = mid + 1;
    // most important part, double pointer loop between two group to find the smallest value
    while (i <= mid && j <= right)
    {
        if (data[i] <= data[j])
        {
            add(temp, data[i]);
            i++;
        }
        else
        {
            add(temp, data[j]);
            j++;
        }
    }
    // remaining value in i group
    while (i <= mid)
    {
        add(temp, data[i]);
        i++;
    }
    // remaining value in j group
    while (j <= right)
    {
        add(temp, data[j]);
        j++;
    }
    for (int k = 0; k < length(temp); k++)
    {
        data[left + k] = temp[k];
    }
}

// for recursion, three param
void merge_sort(fixed_array<int, DATA_SIZE> &data, int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int mid = (left + right) / 2;
    merge_sort(data, left, mid);
    merge_sort(data, mid + 1, right);
    merge(data, left, mid, right);
}

// overload, for calling
void merge_sort(fixed_array<int, DATA_SIZE> &data)
{
    merge_sort(data, 0, DATA_SIZE - 1);
}

int main()
{
    open_window("Merge Sort", WINDOW_WIDTH, WINDOW_HEIGHT);
    fixed_array<int, DATA_SIZE> array;
    fill_array(array);
    return 0;
}