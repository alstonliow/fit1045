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

    // Reject anything that is not an integer
    while (!is_integer(user_input))
    {
        write_line("Please enter a whole number.");
        user_input = read_string(prompt);
    }

    // Safe to convert now that the text is a number
    return to_integer(user_input);
}

// Keep asking until the user types an integer between low and high
int read_integer(string prompt, int low, int high)
{
    // Reuse the version above so the value is already a number
    int value = read_integer(prompt);

    // Reject anything outside the range
    while (value < low || value > high)
    {
        write_line("Please enter a value between " + to_string(low) + " and " + to_string(high));
        value = read_integer(prompt);
    }

    return value;
}

// Read a decimal number from the user
double read_double(string prompt)
{
    string user_input = read_string(prompt);

    return to_double(user_input);
}

// Keep asking until the user types a decimal number that is zero or above
double read_non_negative_double(string prompt)
{
    double value = read_double(prompt);

    // Ask again with a warning added to the prompt
    while (is_negative(value))
    {
        value = read_double("Value cannot be negative. " + prompt);
    }
    return value;
}

// Keep asking until the user types a whole number that is zero or above
int read_non_negative_int(string prompt)
{
    int value = read_integer(prompt);

    // Ask again with a warning added to the prompt
    while (is_negative(value))
    {
        value = read_integer("Value cannot be negative. " + prompt);
    }
    return value;
}
