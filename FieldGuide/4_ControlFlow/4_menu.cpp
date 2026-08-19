#include "splashkit.h"

int main()
{
    string line;
    int choice;

    do
    {
        write_line("1: Addition");
        write_line("2: Subtraction");
        write_line("3: Multiplication");
        write_line("4: Division");
        write_line("5: Quit");
        write("Enter your choice: ");
        line = read_line();

        while (!is_integer(line))
        {
            write_line("Please enter a whole number");
            write_line("Enter your choice: ");
            line = read_line();
        }

        choice = to_integer(line);

        switch (choice)
        {
        case 1:
            write_line("Addition");
            break;
        case 2:
            write_line("Subtraction");
            break;
        case 3:
            write_line("Multiplication");
            break;
        case 4:
            write_line("Division");
            break;
        case 5:
            write_line("Quit");
            break;
        default:
            write_line("Invalid choice");
            break;
        }
    } while (choice != 5);
}