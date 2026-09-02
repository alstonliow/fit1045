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

// determine the color of the bar to highlight the bar
color get_bubble_color(int index, int highlight_index1, int highlight_index2)
{
    // ternary operator
    // [expression to test] ? [if true, return this] : [otherwise, return this]
    // highlight with yellow
    return (index == highlight_index1 || index == highlight_index2) ? COLOR_YELLOW : COLOR_WHITE;
}

/**
 * Determine the color of a single bar during a merge step.
 *
 *   COLOR_YELLOW       -> the bar at position i (left pointer, currently being compared)
 *   COLOR_RED          -> the bar at position j (right pointer, currently being compared)
 *   COLOR_AQUA         -> a bar inside the left half [left, mid], not currently pointed to by i
 *   COLOR_PALE_GREEN   -> a bar inside the right half [mid+1, right], not currently pointed to by j
 *   COLOR_WHITE        -> a bar outside the current [left, right] range (already merged, or not yet reached by this recursive call)
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
color get_merge_color(int index, int left, int mid, int right, int i, int j)
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
        return COLOR_AQUA;
    }
    else if (index >= mid + 1 && index <= right)
    {
        return COLOR_PALE_GREEN;
    }
    else
    {
        return COLOR_WHITE;
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
color get_insert_color(int index, int key_index, int compare_index)
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

// draw bar
void visualise_bubble(const fixed_array<int, DATA_SIZE> &data, int highlight_index1, int highlight_index2)
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

        fill_rectangle(get_bubble_color(i, highlight_index1, highlight_index2), x, y, bar_width, bar_height);
    }

    refresh_screen();
}

// visualise, draw the bar
void visualise_merge(const fixed_array<int, DATA_SIZE> &data, int left, int mid, int right, int i, int j)
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

        // using get_merge_color to determine the color
        fill_rectangle(get_merge_color(k, left, mid, right, i, j), x, y, bar_width, bar_height);
    }

    refresh_screen();
    delay(50);
}

// draw all the bar
void visualise_insert(const fixed_array<int, DATA_SIZE> &data, int key_index, int compare_index)
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

        // using get_insert_color to determine the color
        fill_rectangle(get_insert_color(i, key_index, compare_index), x, y, bar_width, bar_height);
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
        // here giving get_bubble_color() index1 and index2
        // when swap i and i + 1, highlight two bar
        visualise_bubble(data, i, i + 1);
        delay(100); // slow things down so the change is visible
    }
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
        visualise_insert(data, key_pos, i);
        delay(50);
    }

    data[i + 1] = key;
}

/**
 * Merge two already-sorted halves [left, mid] and [mid+1, right]
 * back into a single sorted range [left, right], using two pointers
 * (i, j) to pick the smaller candidate at each step.
 *
 * A final visualise call with -1 indices clears the highlight once
 * this range is fully merged.
 *
 * @param data  the array being sorted (modified in place)
 * @param left  start of the range being merged
 * @param mid   boundary between the two halves
 * @param right end of the range being merged
 */
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
        visualise_merge(data, left, mid, right, i, j);
    }
    // remaining value in i group
    while (i <= mid)
    {
        add(temp, data[i]);
        i++;
        visualise_merge(data, left, mid, right, i, j);
    }
    // remaining value in j group
    while (j <= right)
    {
        add(temp, data[j]);
        j++;
        visualise_merge(data, left, mid, right, i, j);
    }
    for (int k = 0; k < length(temp); k++)
    {
        data[left + k] = temp[k];
    }
    visualise_merge(data, left, mid, right, i, j);
    visualise_merge(data, -1, -1, -1, -1, -1);
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

// full insertion sort
void insertion_sort(fixed_array<int, DATA_SIZE> &data)
{
    for (int j = 1; j <= DATA_SIZE - 1; j++)
    {
        insertion_pass(data, j);
    }
}

/**
 * Recursively sort data[left..right] using merge sort: split at
 * the midpoint, sort each half, then merge them.
 *
 * @param data  the array being sorted (modified in place)
 * @param left  start index of the range to sort
 * @param right end index of the range to sort
 */
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
    fixed_array<int, DATA_SIZE> data;
    int option = 0;

    while (!quit_requested() && option != 4)
    {
        process_events();

        write_line("1: Bubble Sort");
        write_line("2: Insertion Sort");
        write_line("3: Merge Sort");
        write_line("4: Quit");
        write("Enter your option: ");
        option = to_integer(read_line());

        switch (option)
        {
        case 1:
            open_window("Bubble sort", WINDOW_WIDTH, WINDOW_HEIGHT);
            fill_array(data);
            bubble_sort(data);
            delay(100);
            break;
        case 2:
            open_window("Insertion sort", WINDOW_WIDTH, WINDOW_HEIGHT);
            fill_array(data);
            insertion_sort(data);
            delay(100);
            break;
        case 3:
            open_window("Merge sort", WINDOW_WIDTH, WINDOW_HEIGHT);
            fill_array(data);
            merge_sort(data);
            delay(100);
            break;
        case 4:
            break;
        default:
            write_line("Invalid option, please try again.");
            break;
        }
    }
    return 0;
}