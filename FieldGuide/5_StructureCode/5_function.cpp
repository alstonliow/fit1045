#include "splashkit.h"

/**
 * @param prompt
 */

string read_string(string prompt)
{
    write(prompt);
    return read_line();
}

int read_integer(string prompt)
{
    string input = read_string(prompt);

    while (!is_integer(input))
    {
        write_line("Please enter a whole number.");
        input = read_string(prompt);
    }

    return to_integer(input);
}

int read_integer(string prompt, int low, int high)
{
    int input = read_integer(prompt);

    while (input < low || input > high)
    {
        write_line("Please enter a value between " + to_string(low) + " and " + to_string(high));
        input = read_integer(prompt);
    }

    return input;
}

int main()
{
    string name{};
    int age{}, min{}, max{}, value{};

    // Read in a string and store it in name
    name = read_string("Enter your name: ");

    // Output the name
    write_line("Hello " + name);

    // Read in an integer
    age = read_integer("What is your age: ");

    write_line("You are " + to_string(age));

    // read a integer with a range
    min = read_integer("Please choose minimum value. Enter a integer: ");
    max = read_integer("Please choose maximum value. Enter a integer: ");

    value = read_integer("Enter a value between " + to_string(min) + " and " + to_string(max) + ": ", min, max);
    write_line("You entered " + to_string(value));

    return 0;
}