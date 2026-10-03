#include "splashkit.h"
#include "utilities.h"
#include "cheese-shop.h"

#include <format>
using std::format;

/**
 * compile command:
 *
 *  clang++ -std=c++20 cheese-shop.cpp cheese-shop-cli.cpp utilities.cpp -l splashkit -o cheese-shop -Wall
 *
 */

/**
 * The list of option in the main menu
 *
 * @option EXIT_MAIN_MENU
 * @option ADD_CHEESE_MENU
 * @option PRINT_STOCK_LIST_MENU
 */
enum main_menu_option
{
    EXIT_MAIN_MENU,
    ADD_CHEESE_MENU,
    PRINT_STOCK_LIST_MENU
};

void print_cheese(const cheese_data &cheese, bool with_full)
{
    write_line(cheese_to_string(cheese, with_full));
}

/**
 * Read the cheese data from user and return
 *
 *@return the cheese data
 */
cheese_data read_cheese()
{
    cheese_data cheese;

    cheese.name = read_string("Enter a cheese name: ");
    cheese.weight = read_double("Enter weight in stock (kg): ");
    cheese.price = read_integer("Enter the price per kg (cents): ");

    return cheese;
}

/**
 * Perform the step need to ADD_CHEESE_MENU cheese to the shop
 *
 * @param shop the shop
 */
void handle_add_cheese(shop_data &shop)
{
    cheese_data new_cheese = read_cheese();
    add_cheese(shop, new_cheese);
}

/**
 * Show the main menu and get the option
 *
 * @return option
 */
main_menu_option read_main_menu_option()
{
    write_line("0. EXIT_MAIN_MENU");
    write_line("1. ADD_CHEESE_MENU cheese");
    write_line("2. Print cheese list");

    return (main_menu_option)read_integer("Select an option (0-2): ", 0, 2);
}

/**
 * Output the list of stock in the shop
 *
 * @param shop the shop with the cheese data to output
 */
void print_stock_list(const shop_data &shop)
{
    if (shop.cheeses.length() == 0)
    {
        write_line("No cheese");
        return;
    }

    write_line();
    write_line("==============================");
    write_line("Cheese stock list: ");
    write_line("==============================");

    for (int i = 0; i < shop.cheeses.length(); i++)
    {
        print_cheese(shop.cheeses[i], true);
    }

    write_line("==============================");
    write_line();
}

int main()
{
    shop_data shop;
    main_menu_option choice;

    do
    {
        choice = read_main_menu_option();

        switch (choice)
        {
        case EXIT_MAIN_MENU:
            write_line("EXIT_MAIN_MENUing......");
            break;
        case ADD_CHEESE_MENU:
            handle_add_cheese(shop);
            break;
        case PRINT_STOCK_LIST_MENU:
            print_stock_list(shop);
            break;
        }
    } while (choice != EXIT_MAIN_MENU);

    return 0;
}