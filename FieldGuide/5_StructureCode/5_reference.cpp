#include "splashkit.h"

/**
 * swap two value
 * 
 * @param x first integer
 * @param y second integer
 */

void swap(int &x, int &y)
{
    int temp;

    temp = x;

    x = y;

    y = temp;
}

int main()
{
    int num_a, num_b;

    num_a = 2;
    num_b = 8;

    // First print the numbers as-is
    write_line("Before the swap:");
    write_line("num_a is " + to_string(num_a));
    write_line("num_b is " + to_string(num_b));

    // Swap the values of the two variables
    swap(num_a, num_b);

    // Print the numbers afterwards - they should be swapped
    write_line("\nAfter the swap:");
    write_line("num_a is " + to_string(num_a));
    write_line("num_b is " + to_string(num_b));

    return 0;
}