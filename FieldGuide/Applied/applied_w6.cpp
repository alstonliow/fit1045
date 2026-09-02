#include "splashkit.h"

enum difficulty_level
{
    EASY = 1,
    DIFFICULT,
    HARD
};

struct rectangle_struct
{
    double width;
    double height;
};

void check_expensive(double price)
{
    if (price <= 50)
    {
        write_line("the item is cheap.");
    }
    else
    {
        write_line("the item is expensive");
    }
}

double convert_to_miles(double km)
{
    return km * 0.6213711922;
}

void double_number(double &num)
{
    num *= 2;
}

int main()
{
    // 1
    check_expensive(30);
    check_expensive(200);

    // 2
    write_line(convert_to_miles(5));

    // 3
    double value = 30;
    double_number(value);
    write_line(to_string(value));

    // 4
    difficulty_level diff;

    write_line("Choose difficulty level - 1, 2 or 3: ");
    int level = to_integer(read_line());
    diff = (difficulty_level)level;

    write_line("You have choosen level " + to_string(diff));

    // 5
    rectangle_struct rect;

    write_line("Enter width: ");
    rect.width = to_double(read_line());
    write_line("Enter height: ");
    rect.height = to_double(read_line());

    write_line("Your rectangle have a area of " + to_string(rect.width * rect.height));

    return 0;
}