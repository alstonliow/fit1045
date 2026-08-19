#include "utilities.h"
#include "splashkit.h"

string read_string(string prompt)
{
    write(prompt);
    return read_line();
}

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

double read_double(string prompt)
{
    string user_input = read_string(prompt);

    return to_double(user_input);
}

double read_non_negative_double(string prompt)
{
    double value = read_double(prompt);
    while (is_negative(value))
    {
        value = read_double("Value cannot be negative. " + prompt);
    }
    return value;
}

int read_non_negative_int(string prompt)
{
    int value = read_integer(prompt);
    while (is_negative(value))
    {
        value = read_integer("Value cannot be negative. " + prompt);
    }
    return value;
}
