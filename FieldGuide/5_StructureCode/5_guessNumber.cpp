#include "splashkit.h"

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

/**
 *
 * print text to terminala number of line, allowing repeat
 *
 * @param text
 * @param times
 * @param with_newline
 *
 */

void print_repeated(string text, int times, bool with_newline)
{
    int i = 0;

    while (i < times)
    {
        write(text);
        i++;
    }

    if (with_newline)
    {
        write('\n');
    }
}

/**
 *
 * print a line
 *
 * @param length length of line to print
 *
 */

void print_line(int length)
{
    print_repeated("-", length, true);
}

/**
 *
 * @param guess_number
 * @param target
 *
 */

bool perform_guess(int guess_number, int target)
{
    int guess;

    guess = read_integer("Guess " + to_string(guess_number) + ": ");

    if (target < guess)
    {
        write_line("The number is less than " + to_string(guess));
    }

    else if (target > guess)
    {
        write_line("The number is larger than " + to_string(guess));
    }

    else
    {
        write_line("Well done! the number was " + to_string(guess));
    }

    return target == guess;
}

/**
 * generate random number, player guess it
 */

const int MAX_NUMBER = 100;
const int MIN_NUMBER = 1;
const int MAX_GUESS = 6;

void play_game()
{
    int my_number{}, guess_number{};
    bool got_it{};

    my_number = rnd(MIN_NUMBER, MAX_NUMBER);
    guess_number = 0;
    write_line("Guess a number between " + to_string(MIN_NUMBER) + " and " + to_string(MAX_NUMBER));

    do
    {
        guess_number++;
        got_it = perform_guess(guess_number, my_number);
    } while (guess_number < MAX_GUESS && !got_it);

    if (!got_it)
    {
        write_line("You ran out of the guesses... the number was " + to_string(my_number));
    }
}

int main()
{
    string again{};

    do
    {
        play_game();
        write_line();
        print_line(50);

        again = read_string("Do you want to play again [Y/n]? ");

    } while (again != "N" && again != "n");

    write_line("Bye");
    return 0;
}