#include "splashkit.h"
#include "utilities.h"
#include "splashkit-arrays.h"

const int NO_CHOICE = -1;

enum menu_option
{
    ADD_PRODUCT = 1,
    DELETE_PRODUCT = 2,
    UPDATE_PRODUCT = 3,
    SELL_PRODUCT = 4,
    PRINT_STATUS = 5,
    LIST_PRODUCTS = 6,
    QUIT = 7
};

struct product_data
{
    string name{};
    double cost_price{};
    double sale_price{};
    int stock{0};
};

struct store_data
{
    dynamic_array<product_data> products{};
    double total_sales{0};
    double total_profits{0};
};

void print_product(const product_data &product)
{
    write_line("Product name : " + product.name);
    write_line("Cost price: " + to_string(product.cost_price));
    write_line("Sale price: " + to_string(product.sale_price));
    write_line("Product stock: " + to_string(product.stock));
}

// read the new product
product_data read_product()
{
    product_data product{};

    product.name = read_string("Enter product name: ");

    while (product.name.length() == 0)
    {
        product.name = read_string("Name cannot be empty. Enter product name: ");
    }

    // read positive integer and double
    product.cost_price = read_non_negative_double("Enter product cost price: ");
    product.sale_price = read_non_negative_double("Enter product sale price: ");
    product.stock = read_non_negative_int("Enter product stock: ");

    return product;
}

void add_product(store_data &store)
{
    product_data product = read_product();

    add(store.products, product);

    write_line("Product '" + product.name + "' added to store.");
}

void list_product(const store_data &store)
{
    for (int i = 0; i < length(store.products); i++)
    {
        write("Product " + to_string(i + 1) + " : ");
        print_product(store.products[i]);
    }
    write_line("There are total of " + to_string(length(store.products)) + " products.");
}

// find product and return with it index
// with a array matches rearrange the index
int find_product(const store_data &store)
{
    // quit find_product() if there are no product in store
    if (length(store.products) == 0)
    {
        write_line("There are no product in store.");
        return NO_CHOICE;
    }

    string search_text = read_string("Enter the name product you want to search.");
    dynamic_array<int> matches;

    // loop the products list
    for (int i = 0; i < length(store.products); i++)
    {
        if (contains(store.products[i].name, search_text))
        {
            add(matches, i);
            write_line(to_string(length(matches)) + ". " + store.products[i].name);
        }
    }

    if (length(matches) == 0)
    {
        write_line("No matching product.");
        return NO_CHOICE;
    }

    int index = read_integer("Enter a index to choose a product: ", 1, length(matches)) - 1;

    return matches[index];
}

void sell_product(store_data &store)
{
    int index = find_product(store);
    if (index == NO_CHOICE)
    {
        return;
    }

    if (store.products[index].stock == 0)
    {
        write_line("No stock available for this product.");
        return;
    }

    int units = read_integer("Enter the number of units sold: ", 0, store.products[index].stock);

    double sales_total = store.products[index].sale_price * units;
    double profit_total = sales_total - store.products[index].cost_price * units;

    store.products[index].stock -= units;
    store.total_sales += sales_total;
    store.total_profits += profit_total;

    write_line("Sold " + to_string(units) + " units");
    write_line("Revenue: $" + to_string(sales_total, 2) + ", Profit $" + to_string(profit_total, 2));
}

void delete_product(store_data &store)
{
    int index = find_product(store);
    if (index == NO_CHOICE)
    {
        return;
    }

    string deleted_product = store.products[index].name;

    remove(store.products, index);

    write_line("Deleted " + deleted_product);
}

void print_status(const store_data &store)
{
    double stock_value = 0;
    int low_stock = 0;

    for (int i = 0; i < length(store.products); i++)
    {
        stock_value += store.products[i].cost_price * store.products[i].stock;

        if (store.products[i].stock < 10)
        {
            low_stock++;
        }
    }

    // Print report
    write_line("== Store Report ==");
    write_line("Total sales:     $" + to_string(store.total_sales, 2));
    write_line("Total profit:    $" + to_string(store.total_profits, 2));
    write_line("Products:        " + to_string(length(store.products)));
    write_line("Stock value:     $" + to_string(stock_value, 2));
    write_line("Low stock (<10): " + to_string(low_stock));
}

void print_main_menu()
{
    write_line("Main Menu");
    write_line("1. Add a new product");
    write_line("2. Delete a product");
    write_line("3. Update a product");
    write_line("4. Sell a product");
    write_line("5. Print status");
    write_line("6. List products");
    write_line("7. Quit");
}

enum update_product_option
{
    UPDATE_NAME = 1,
    UPDATE_COST_PRICE = 2,
    UPDATE_SALE_PRICE = 3,
    UPDATE_STOCK = 4,
    UPDATE_QUIT = 5
};

void print_update_menu()
{
    write_line("Update Menu");
    write_line("1. Update name");
    write_line("2. Update cost price");
    write_line("3. Update sale price");
    write_line("4. Update number in stock");
    write_line("5. Quit update");
}

void update_product(store_data &store)
{
    int index = find_product(store);
    if (index == NO_CHOICE)
    {
        return;
    }

    update_product_option option;
    do
    {
        write_line("Current details: ");
        print_product(store.products[index]);
        write_line(" ");
        print_update_menu();
        option = (update_product_option)read_integer("Enter a option: ", 1, 5);

        switch (option)
        {
        case UPDATE_NAME:
            store.products[index].name = read_string("Enter new name: ");
            write_line("Updated name.");
            break;
        case UPDATE_COST_PRICE:
            store.products[index].cost_price = read_non_negative_double("Enter new cost price: ");
            write_line("Updated cost price.");
            break;
        case UPDATE_SALE_PRICE:
            store.products[index].sale_price = read_double("Enter new sale price: ");
            write_line("Updated sale price.");
            break;
        case UPDATE_STOCK:
            store.products[index].stock = read_integer("Enter new amount in stock: ");
            write_line("Updated amount of stock.");
            break;
        case UPDATE_QUIT:
            break;
        }
    } while (option != UPDATE_QUIT);
}

int main()
{
    store_data store{};
    write_line("Product Database!");

    menu_option option;
    do
    {
        print_main_menu();
        option = (menu_option)read_integer("Please choose an option: ", 1, 7);

        switch (option)
        {
        case ADD_PRODUCT:
            add_product(store);
            break;
        case DELETE_PRODUCT:
            delete_product(store);
            break;
        case UPDATE_PRODUCT:
            update_product(store);
            break;
        case SELL_PRODUCT:
            sell_product(store);
            break;
        case PRINT_STATUS:
            print_status(store);
            break;
        case LIST_PRODUCTS:
            list_product(store);
            break;
        case QUIT:
            break;
        }
    } while (option != QUIT);

    write_line("Thank you for using our service. Program Quitting....");

    return 0;
}