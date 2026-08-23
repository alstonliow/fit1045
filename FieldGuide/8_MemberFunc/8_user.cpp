#include "splashkit.h"
#include "utilities.h"

class user
{
    string password{};

public:
    string name{};

    // intialize account with param
    user(string name_, string password_)
    {
        name = name_;
        password = password_;
    }

    // initialize account without param
    user()
    {
        name = "No name";
        password = "";
    }
};

int main()
{
    return 0;
}