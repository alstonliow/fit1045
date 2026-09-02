#include "splashkit.h"
#include "bounded_array.hpp"

// Compare `value` against `expected` - only prints something when they differ,
// so a silent run means all the tests passed.
void test_value(double value, double expected, string fail_message)
{
    if (value != expected)
    {
        write_line(to_string(value) + " != " + to_string(expected) + " | " + fail_message);
    }
}

// Exercises every bounded_array operation, including the error cases
int main()
{
    // A 50-slot array of doubles - starts empty, not full of zeroes
    bounded_array<double, 50> numbers;

    write_line("Running tests - no output means no errors :)");
    write_line("===Tests Start===");

    test_value(numbers.length(), 0, "0 Length failed");

    // ------------ add a few values and read them back
    numbers.add(7);
    test_value(numbers.get(0), 7, "1st Add or Get failed");

    numbers.add(3);
    test_value(numbers.get(1), 3, "2nd Add or Get failed");

    numbers.add(24);
    test_value(numbers.get(2), 24, "3rd Add or Get failed");

    // `get` returns a reference, so it can appear on the left of an assignment
    numbers.get(2) = -8.5; // Change the 24 to -8.5
    test_value(numbers.get(2), -8.5, "Change value via Get failed");

    test_value(numbers.length(), 3, "3 Length failed");

    // ===== Test a variety of exceptions ===== //

    // ------------ fill up the array to test capacity handling
    try
    {
        while (numbers.length() < numbers.capacity())
        {
            numbers.add(0);
        }
    }
    catch (const array_full &e)
    {
        write_line("Add stopped adding elements before reaching capacity");
    }

    // ------------ test adding an element to a full array
    try
    {
        numbers.add(0);
        write_line("Add continued adding elements past max capacity");
    }
    catch (const array_full &e)
    {
        /* we expected an error, so this is success! So no output */
    }

    // ------------ test accessing negative indexes
    try
    {
        numbers.get(-4);
        write_line("Accessing index -4 didn't error!");
    }
    catch (const array_invalid_index &e)
    {
        /* we expected an error, so this is success! So no output */
    }

    // ------------ test accessing indexes larger than the maximum capacity
    try
    {
        numbers.get(numbers.capacity());
        write_line("Accessing index MAX_CAPACITY didn't error!");
    }
    catch (const array_invalid_index &e)
    {
        /* we expected an error, so this is success! So no output */
    }

    // ------------ test remove - dropping index 1 should shift -8.5 down into it
    numbers.remove(1);
    test_value(numbers.length(), numbers.capacity() - 1, "3 Remove failed (length didn't decrease)");
    test_value(numbers.get(1), -8.5, "Remove failed (element didn't shift)");

    write_line("===Tests End===");
}