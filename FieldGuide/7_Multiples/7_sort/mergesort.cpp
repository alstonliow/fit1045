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

int main()
{
    return 0;
}