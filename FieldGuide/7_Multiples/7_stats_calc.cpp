#include "splashkit.h"
#include "utilities.h"
#include "splashkit-arrays.h"

void populate_array(dynamic_array<double> &data)
{
    int size = read_integer("How many values do you want to enter? ");

    if (size < 0)
    {
        size = 0;
    }

    for (int i = 0; i < size; i++)
    {
        add(data, read_double("Enter value: "));
    }
}

void print(const dynamic_array<double> &data)
{
    for (int i = 0; i < length(data); i++)
    {
        write_line(to_string(i) + " : " + to_string((data[i]), 2));
    }
}

double max(const dynamic_array<double> &data)
{
    if (length(data) == 0)
    {
        return 0;
    }

    double max = data[0];

    for (int i = 0; i < length(data); i++)
    {
        if (data[i] >= max)
        {
            max = data[i];
        }
    }

    return max;
}

double sum(const dynamic_array<double> &data)
{
    int i = 0;
    double result = 0;

    for (i = 0; i < length(data); i++)
    {
        result += data[i];
    }

    return result;
}

double mean(const dynamic_array<double> &data)
{
    if (length(data) > 0)
    {
        return sum(data) / length(data);
    }
    else
    {
        return 0;
    }
}

void add_data(dynamic_array<double> &data)
{
    double value = read_double("Enter a value to add: ");
    add(data, value);
}

void remove_value(dynamic_array<double> &data)
{
    print(data);

    int index = read_integer("Enter a index to remove: ");

    if (index >= 0 && index < length(data))
    {
        remove(data, index);
    }
    else
    {
        write_line("Sorry, this is a invalid index. ");
    }
}

void print_menu()
{
    write_line("\n Menu");
    write_line("1. Add a value");
    write_line("2. Remove a value");
    write_line("3. Print the value");
    write_line("4. Calculate stats");
    write_line("5. Quit");
}

int main()
{
    dynamic_array<double> data;

    populate_array(data);

    print_menu();
    int option = read_integer("Enter a integer (1-5) : ", 1, 5);

    while (option != 5)
    {
        switch (option)
        {
        case 1:
            add_data(data);
            break;
        case 2:
            remove_value(data);
            break;
        case 3:
            write_line("\nYou entered...\n");
            print(data);
            break;
        case 4:
            write_line("\nCalculating statistics...\n");

            write_line("Sum:        " + to_string(sum(data), 2));
            write_line("Mean:       " + to_string(mean(data), 2));
            write_line("Max:        " + to_string(max(data), 2));
            break;
        }
        read_string("Press Enter to continue...");

        print_menu();
        option = read_integer("Enter an option: ", 1, 5);
    }

    write_line("Goodbye!");

    return 0;
}