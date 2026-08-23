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
};

int main()
{
    return 0;
}