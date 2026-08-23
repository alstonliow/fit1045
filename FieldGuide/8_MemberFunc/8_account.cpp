#include "splashkit.h"
#include "utilities.h"

class account
{
    // The balance of account in cent
    int balance{};

public:
    // The name of account holder
    string name{};

    // counstructor with param
    account(string name_, int balance_)
    {
        // initialize the account
        name = name_;
        balance = balance_;
    }

    // constructor without param
    account()
    {
        name = "Account holder unknown";
        balance = 0;
    }

    // print method
    void print()
    {
        write_line(name + ": $" + to_string(balance / 100.0));
    }

    // Only increase the balance if the value is positive.
    void deposit(int amount)
    {
        if (amount > 0)
        {
            balance += amount;
        }
        else
        {
            write_line("Please enter a positive number.");
        }
    }

    // Only decrease the balance if the value is positive.
    void withdraw(int amount)
    {
        if (amount > 0)
        {
            balance -= amount;
        }
        else
        {
            write_line("Please enter a positive number.");
        }
    }

    // return the balance
    int get_balance()
    {
        return balance;
    }
};

int main()
{
    // test
    // Create an account
    account a1("Atabak", 1000);
    a1.print();

    // Deposit a positive amount - should work
    write_line("Depositing 500...");
    a1.deposit(500);
    a1.print();

    // Deposit a negative amount - should be rejected
    write_line("Depositing -200...");
    a1.deposit(-200);
    a1.print();

    // Withdraw a positive amount - should work
    write_line("Withdrawing 300...");
    a1.withdraw(300);
    a1.print();

    // Withdraw a negative amount - should be rejected
    write_line("Withdrawing -100...");
    a1.withdraw(-100);
    a1.print();

    // Use get_balance to read the value directly
    write_line("Current balance (cents): " + to_string(a1.get_balance()));

    return 0;
}