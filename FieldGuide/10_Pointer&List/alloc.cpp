#include "splashkit.h"
#include "utilities.h"

// ptr:     address
// *ptr:    value in address

/**
 * An account value storing the name and balance of an account.
 *
 * @field name The name of the account.
 * @field balance The amount of funds allocated to the account.
 */
struct account
{
    string name;
    int balance;
};

/**
 * Print the account details to the terminal.
 *
 * @param act the account to print.
 */
void print_account(account &act)
{
    write_line("Name: " + act.name);
    write_line("Balance: " + to_string(act.balance));
}

int main()
{
    // TODO: declare an account pointer

    // TODO: Create a new account on the heap
    account *ptr;
    ptr = new account;

    // TODO: Allocate details to the account's fields
    ptr->name = "My Account";
    ptr->balance = 154;

    // TODO: Print the account using the pointer
    write_line("Name: " + ptr->name);
    write_line("Balance: " + to_string(ptr->balance));

    // TODO: Print the account using the function
    print_account(*ptr);

    // TODO: Clean up
    delete ptr;
    ptr = nullptr;
}