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
    EDIT_CHEESE_MENU,
    DELETE_CHEESE_MENU,
    PRINT_STOCK_LIST_MENU,
    ADD_ORDER_MENU,
    PRINT_ORDERS_MENU
};

void print_cheese(const cheese_data &cheese, bool with_full)
{
    write_line(cheese_to_string(cheese, with_full));
}

/**
 * Read the cheese data from user and return
 *
 * @return the cheese data
 */
cheese_data read_cheese()
{
    cheese_data cheese;
    string error_message;
    bool valid;

    do
    {
        cheese.name = read_string("Enter a cheese name: ");
        cheese.weight = read_double("Enter weight in stock (kg): ");
        cheese.price = read_integer("Enter the price per kg (cents): ");

        valid = cheese_valid(cheese, error_message);

        if (!valid)
        {
            write_line(error_message);
        }
    } while (!valid);

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
    write_line("0. Exit main menu");
    write_line("1. Add cheese");
    write_line("2. Edit cheese");
    write_line("3. Delete cheese");
    write_line("4. Print cheese list");
    write_line("5. Add order");
    write_line("6. Print orders and sales");

    return (main_menu_option)read_integer("Select an option (0-6): ", 0, 6);
}

void print_cheese_list(const dynamic_array<cheese_data> &cheeses, bool with_ids)
{
    for (int i = 0; i < cheeses.length(); i++)
    {
        if (with_ids)
        {
            write(format("{}: ", i + 1));
        }
        print_cheese(cheeses[i], true);
    }
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

    print_cheese_list(shop.cheeses, true);

    write_line("==============================");
    write_line();
}

int select_cheese(const dynamic_array<cheese_data> &cheeses)
{
    if (cheeses.length() == 0)
    {
        write_line("No cheese in stock.");
        return -1;
    }

    write_line("0: Select none");
    print_cheese_list(cheeses, false);

    return read_integer("Select cheese: ", 0, cheeses.length()) - 1;
}

/**
 * Allow user to edit the cheese
 *
 * @param cheese a reference of cheese to be updated
 */
void edit_cheese(cheese_data &cheese)
{
    write_line("Editing cheese: " + cheese_to_string(cheese, true));

    if (read_integer("Edit the name? (1 for yes, 0 for no): ", 0, 1) == 1)
    {
        cheese.name = read_string("Enter new cheese name: ");
    }

    if (read_integer("Edit the weight? (1 for yes, 0 for no): ", 0, 1) == 1)
    {
        cheese.weight = read_double("Enter new weight in stock (kg): ");
    }

    if (read_integer("Edit the price? (1 for yes, 0 for no): ", 0, 1) == 1)
    {
        cheese.price = read_integer("Enter new price per kg (cents): ");
    }
}

/**
 * Perform the steps to allow the user to edit a cheese in the shop.
 *
 * @param shop the shop with the cheese to be edited
 */
void handle_edit_cheese(shop_data &shop)
{
    int index = select_cheese(shop.cheeses);

    if (index == -1)
    {
        return;
    }

    edit_cheese(shop.cheeses[index]);
}

/**
 * Perform the steps to allow the user to delete a cheese from the shop.
 *
 * @param shop the shop with the cheese to be deleted
 */
void handle_delete_cheese(shop_data &shop)
{
    int index = select_cheese(shop.cheeses);

    if (index == -1)
    {
        return;
    }

    delete_cheese(shop, index);
}

/**
 * Read an order from the user. The user repeatedly selects a cheese from
 * the stock and enters the weight wanted, until they select none.
 *
 * @param shop the shop with the cheese in stock
 * @return order_data the order read from the user
 */
order_data read_order(const shop_data &shop)
{
    order_data order;

    while (true)
    {
        int index = select_cheese(shop.cheeses);

        if (index == -1)
        {
            break;
        }

        cheese_data stock = shop.cheeses[index];
        double amount = read_double("Enter weight to order (kg): ");

        if (amount <= 0 || amount > stock.weight)
        {
            write_line("Weight must be above 0 and not more than the stock.");
            continue;
        }

        add_cheese_to_order(order, new_cheese(stock.name, amount, stock.price));
    }

    return order;
}

/**
 * Perform the steps needed to create an order and add it to the shop.
 *
 * @param shop the shop where the order is to be added
 */
void handle_add_order(shop_data &shop)
{
    order_data order = read_order(shop);

    if (order.items.length() == 0)
    {
        write_line("Empty order, nothing added.");
        return;
    }

    add_order(shop, order);
}

/**
 * Output all orders in the shop, followed by the total sales.
 *
 * @param shop the shop with the orders to output
 */
void print_orders(const shop_data &shop)
{
    if (shop.orders.length() == 0)
    {
        write_line("No orders");
        return;
    }

    int sales = 0;

    write_line();
    write_line("===================================");
    write_line("Orders:");
    write_line("===================================");

    for (int i = 0; i < shop.orders.length(); i++)
    {
        write_line(format("Order {}:", i + 1));
        print_cheese_list(shop.orders[i].items, false);
        write_line(format("Order total: ${:.2f}", order_total_cost(shop.orders[i]) / 100.0));
        write_line();

        sales += order_total_cost(shop.orders[i]);
    }

    write_line("===================================");
    write_line(format("Total sales: ${:.2f}", sales / 100.0));
    write_line("===================================");
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
            write_line("Exiting......");
            break;
        case ADD_CHEESE_MENU:
            handle_add_cheese(shop);
            break;
        case EDIT_CHEESE_MENU:
            handle_edit_cheese(shop);
            break;
        case DELETE_CHEESE_MENU:
            handle_delete_cheese(shop);
            break;
        case PRINT_STOCK_LIST_MENU:
            print_stock_list(shop);
            break;
        case ADD_ORDER_MENU:
            handle_add_order(shop);
            break;
        case PRINT_ORDERS_MENU:
            print_orders(shop);
            break;
        }
    } while (choice != EXIT_MAIN_MENU);

    return 0;
}