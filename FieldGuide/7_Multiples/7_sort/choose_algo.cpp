#include "splashkit.h"
#include "splashkit-arrays.h"

// change DATA_SIZE to changing the number of bar
const int DATA_SIZE = 100;
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const string WINDOW_TITLE = "Sort Visualiser";

// how long to wait after each step
const int STEP_DELAY = 10;

// the menu options
enum sort_option
{
    BUBBLE_SORT = 1,
    INSERTION_SORT = 2,
    MERGE_SORT = 3,
    QUIT = 4,
    INVALID = 0
};

// change the number user type into the option name
// if the number is not in the menu, return INVALID
sort_option to_sort_option(int value)
{
    switch (value)
    {
    case BUBBLE_SORT:
        return BUBBLE_SORT;
    case INSERTION_SORT:
        return INSERTION_SORT;
    case MERGE_SORT:
        return MERGE_SORT;
    case QUIT:
        return QUIT;
    default:
        return INVALID;
    }
}

// fill array random
void fill_array(fixed_array<int, DATA_SIZE> &data)
{
    for (int i = 0; i < length(data); i++)
    {
        data[i] = rnd(1, WINDOW_HEIGHT);
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
 * Determine the color of a single bar when merging.
 *
 *   COLOR_YELLOW     -> the bar at i, left pointer comparing now
 *   COLOR_RED        -> the bar at j, right pointer comparing now
 *   COLOR_AQUA       -> in the left half [left, mid], but not at i
 *   COLOR_PALE_GREEN -> in the right half [mid+1, right], but not at j
 *   COLOR_WHITE      -> outside [left, right], this merge does not touch it
 *
 * @param index the bar being drawn now (0 .. DATA_SIZE-1)
 * @param left  start of the range being merged
 * @param mid   split point, left half is [left, mid], right half is [mid+1, right]
 * @param right end of the range being merged
 * @param i     the left half pointer
 * @param j     the right half pointer
 * @return the color to draw this bar with
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
    double bar_width = (double)screen_width() / length(data);

    clear_screen(COLOR_BLACK);

    for (int i = 0; i < length(data); i++)
    {
        // The value is the height, so just find the top-left corner of the bar.
        // Screen y grows downwards, so a taller bar starts higher up.
        double bar_height = (double)data[i];
        double x = i * bar_width; // actually (i+1)-1=i, the width of the pass one
        double y = screen_height() - bar_height;

        fill_rectangle(get_bubble_color(i, highlight_index1, highlight_index2), x, y, bar_width, bar_height);
    }

    refresh_screen();

    // must call, if not splashkit cannot see the X button click
    // quit_requested() stay true after that, so main can check it later
    process_events();
}

// visualise, draw the bar
void visualise_merge(const fixed_array<int, DATA_SIZE> &data, int left, int mid, int right, int i, int j)
{
    double bar_width = (double)screen_width() / length(data);
    clear_screen(COLOR_BLACK);

    for (int k = 0; k < length(data); k++)
    {
        // The value is the height, so just find the top-left corner of the bar.
        // Screen y grows downwards, so a taller bar starts higher up.
        double bar_height = (double)data[k];
        double x = k * bar_width;
        double y = (double)screen_height() - bar_height;

        // using get_merge_color to determine the color
        fill_rectangle(get_merge_color(k, left, mid, right, i, j), x, y, bar_width, bar_height);
    }

    // only draw here, the caller do the delay
    refresh_screen();
    process_events();
}

// draw all the bar
void visualise_insert(const fixed_array<int, DATA_SIZE> &data, int key_index, int compare_index)
{
    // Split the window width evenly between the elements.
    double bar_width = (double)screen_width() / length(data);

    clear_screen(COLOR_BLACK);

    for (int i = 0; i < length(data); i++)
    {
        // The value is the height, so just find the top-left corner of the bar.
        // Screen y grows downwards, so a taller bar starts higher up.
        double bar_height = (double)data[i];
        double x = i * bar_width; // actually (i+1)-1=i, the width of the pass one
        double y = screen_height() - bar_height;

        // using get_insert_color to determine the color
        fill_rectangle(get_insert_color(i, key_index, compare_index), x, y, bar_width, bar_height);
    }

    refresh_screen();
    process_events();
}

// bubble sort one time, biggest one move to the end
void bubble_sort_pass(fixed_array<int, DATA_SIZE> &data, int range)
{
    // swap of i and i+1, so need (range - 1)
    for (int i = 0; i < range - 1; i++)
    {
        // user click the X, stop the sort now
        if (quit_requested())
        {
            return;
        }

        // here giving get_bubble_color() index1 and index2
        // draw before swap, so can see which pair is comparing
        visualise_bubble(data, i, i + 1);
        delay(STEP_DELAY); // slow things down so the change is visible

        // Out of order? Swap the pair using a temporary variable.
        if (data[i] > data[i + 1])
        {
            int temp = data[i];
            data[i] = data[i + 1];
            data[i + 1] = temp;
        }

        // draw after swap, so can see the result
        visualise_bubble(data, i, i + 1);
        delay(STEP_DELAY);
    }
}

// insertion sort one time
void insertion_pass(fixed_array<int, DATA_SIZE> &data, int key_pos)
{
    int key = data[key_pos]; // current key
    int i = key_pos - 1;     // last position of sorted data

    while (i >= 0 && data[i] > key && !quit_requested())
    {
        // all element before the key compare with key
        // if element > key, then move right
        data[i + 1] = data[i];
        i = i - 1; // move left to campare with key again

        // visualise with highlight
        visualise_insert(data, key_pos, i);
        delay(STEP_DELAY);
    }

    // key go to its position, draw it also, if not this step cannot see
    data[i + 1] = key;
    visualise_insert(data, i + 1, -1);
    delay(STEP_DELAY);
}

/**
 * Merge the two sorted halves [left, mid] and [mid+1, right] back into
 * one sorted range [left, right]. Two pointers (i, j) take the smaller
 * one each time.
 *
 * The last visualise with -1 is to clear the highlight after this range
 * is done.
 *
 * @param data  the array to sort, changed in place
 * @param left  start of the range being merged
 * @param mid   split point between the two halves
 * @param right end of the range being merged
 */
void merge(fixed_array<int, DATA_SIZE> &data, int left, int mid, int right)
{
    // stop before start, if quit in the middle the temp is not complete
    // and copy back will break the array
    if (quit_requested())
    {
        return;
    }

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
        delay(STEP_DELAY);
    }
    // remaining value in i group
    while (i <= mid)
    {
        add(temp, data[i]);
        i++;
        visualise_merge(data, left, mid, right, i, j);
        delay(STEP_DELAY);
    }
    // remaining value in j group
    while (j <= right)
    {
        add(temp, data[j]);
        j++;
        visualise_merge(data, left, mid, right, i, j);
        delay(STEP_DELAY);
    }
    for (int k = 0; k < length(temp); k++)
    {
        data[left + k] = temp[k];
    }
    visualise_merge(data, left, mid, right, i, j);
    delay(STEP_DELAY);
    visualise_merge(data, -1, -1, -1, -1, -1);
    delay(STEP_DELAY);
}

// full bubble sort, every pass one less element to check
void bubble_sort(fixed_array<int, DATA_SIZE> &data)
{
    for (int i = length(data); i > 1 && !quit_requested(); i--)
    {
        bubble_sort_pass(data, i);
    }
}

// full insertion sort
void insertion_sort(fixed_array<int, DATA_SIZE> &data)
{
    for (int j = 1; j < length(data) && !quit_requested(); j++)
    {
        insertion_pass(data, j);
    }
}

/**
 * Sort data[left..right] with merge sort: split at the middle,
 * sort the two halves by recursion, then merge them.
 *
 * @param data  the array to sort, changed in place
 * @param left  start index of the range to sort
 * @param right end index of the range to sort
 */
void merge_sort(fixed_array<int, DATA_SIZE> &data, int left, int right)
{
    // left >= right means only one element, already sorted
    // quit_requested() means user click the X, stop the recursion
    if (left >= right || quit_requested())
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
    merge_sort(data, 0, length(data) - 1);
}

// print the menu
void write_menu()
{
    write_line("1: Bubble Sort");
    write_line("2: Insertion Sort");
    write_line("3: Merge Sort");
    write_line("4: Quit");
    write("Enter your option: ");
}

// fill new random value, then sort with the algorithm user chose
void run_sort(sort_option option, fixed_array<int, DATA_SIZE> &data)
{
    fill_array(data);

    switch (option)
    {
    case BUBBLE_SORT:
        bubble_sort(data);
        break;
    case INSERTION_SORT:
        insertion_sort(data);
        break;
    case MERGE_SORT:
        merge_sort(data);
        break;
    case QUIT:
    case INVALID:
        break; // main already handle these, nothing to sort
    }
}

int main()
{
    fixed_array<int, DATA_SIZE> data;
    sort_option option = INVALID;

    // ask the option first, no window before user choose
    while (option != QUIT && !quit_requested())
    {
        write_menu();
        option = to_sort_option(to_integer(read_line()));

        if (option == INVALID)
        {
            write_line("Invalid option, please try again.");
        }
        else if (option != QUIT)
        {
            open_window(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
            process_events();

            run_sort(option, data);

            // sort finish, keep the window so the result can be seen
            // -1 is not a real index, so no bar get highlighted
            while (!quit_requested() && !any_key_pressed())
            {
                visualise_bubble(data, -1, -1);
                delay(STEP_DELAY);
            }

            close_window(WINDOW_TITLE);
        }
    }

    return 0;
}