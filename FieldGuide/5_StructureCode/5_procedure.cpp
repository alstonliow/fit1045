#include "splashkit.h"

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

int main()
{
    string input;
    int test_length;

    print_line(20);
    write_line("| Line print test  |");
    print_line(20);

    print_repeated("--+--+", 5, true);
    print_repeated("Hello World\n", 5, false);
    print_repeated("--+--+", 5, true);

    write("Enter a length for a test line: ");
    input = read_line();
    test_length = to_integer(input);

    print_line(test_length);

    return 0;
}