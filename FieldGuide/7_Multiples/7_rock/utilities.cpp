#include "utilities.h"
#include "splashkit.h"

// Show the prompt and return whatever the user types
string read_string(string prompt)
{
    write(prompt);
    return read_line();
}

// Keep asking until the user types a whole number
int read_integer(string prompt)
{
    string user_input = read_string(prompt);

    // Reject anything that is not a whole number
    while (!is_integer(user_input))
    {
        write_line("Please enter a whole number.");
        user_input = read_string(prompt);
    }

    return to_integer(user_input);
}

// Keep asking until the user types a whole number inside low..high
int read_integer(string prompt, int low, int high)
{
    int value = read_integer(prompt);

    // Reject values that fall outside the allowed range
    while (value < low || value > high)
    {
        write_line("Please enter a value between " + to_string(low) + " and " + to_string(high));
        value = read_integer(prompt);
    }

    return value;
}

// Read a line and convert it to a double
double read_double(string prompt)
{
    string user_input = read_string(prompt);

    return to_double(user_input);
}

// True when the integer is below zero
bool is_negative(int value)
{
    return value < 0;
}

// True when the double is below zero
bool is_negative(double value)
{
    return value < 0;
}

// Keep asking until the user gives a double that is zero or above
double read_non_negative_double(string prompt)
{
    double value = read_double(prompt);
    while (is_negative(value))
    {
        // Add a warning in front of the original prompt
        value = read_double("Value cannot be negative. " + prompt);
    }
    return value;
}

// Keep asking until the user gives an integer that is zero or above
int read_non_negative_int(string prompt)
{
    int value = read_integer(prompt);
    while (is_negative(value))
    {
        // Add a warning in front of the original prompt
        value = read_integer("Value cannot be negative. " + prompt);
    }
    return value;
}
