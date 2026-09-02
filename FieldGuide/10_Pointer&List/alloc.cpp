#include "splashkit.h"
#include "utilities.h"

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
    ptr = new account();

    // TODO: Allocate details to the account's fields

    // TODO: Print the account using the pointer

    // TODO: Print the account using the function

    // TODO: Clean up
}