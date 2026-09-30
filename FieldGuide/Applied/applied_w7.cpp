#include "splashkit.h"
#include "utilities.h"

struct laptop_data
{
    int id;
    string name;
    double price;
};

void print_details(const laptop_data &laptop)
{
    write_line("ID: " + to_string(laptop.id) + " Owner name: " + laptop.name + " Price: " + to_string(laptop.price));
}

laptop_data read_laptop()
{
    laptop_data laptop;
    laptop.id = read_integer("Enter your ID: ");
    laptop.name = read_string("Enter your name: ");
    laptop.price = read_double("Enter the price: ");
    return laptop;
}

int main()
{
    laptop_data laptop1 = read_laptop();

    print_details(laptop1);

    return 0;
}