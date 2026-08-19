#include "utilities/utilities.h"
#include "splashkit.h"

int main()
{
    string name{};
    int age{};

    name = read_string("Please enter your name: ");
    age = read_integer("Please enter your age: ");

    write_line("Hello " + name + " " + to_string(age));
}