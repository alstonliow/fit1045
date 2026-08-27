#include "splashkit.h"

void display_input(string prompt)
{
    write(prompt);
    string user_input = read_line();
    write_line(user_input);
}

double calculate_rect_area(double width, double height)
{
    return width * height;
}

double con_celsius(double temp)
{
    return (temp - 32) * 5 / 9;
}

int main()
{
    display_input("Enter your name: ");
    write_line(calculate_rect_area(10, 8));
    write_line(con_celsius(90));

    return 0;
}