#include "utilities.h"
#include "splashkit.h"

// Read a string from user
string read_string(string prompt)
{
    write(prompt);
    return read_line();
}

// Read an integer from user
int read_integer(string prompt)
{
    string user_input = read_string(prompt);

    while (!is_integer(user_input))
    {
        write_line("Please enter a whole number.");
        user_input = read_string(prompt);
    }

    return to_integer(user_input);
}

// Read an integer from user, within a given range
int read_integer(string prompt, int low, int high)
{
    int value = read_integer(prompt);

    while (value < low || value > high)
    {
        write_line("Please enter a value between " + to_string(low) + " and " + to_string(high));
        value = read_integer(prompt);
    }

    return value;
}
