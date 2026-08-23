#include "splashkit.h"
#include "utilities.h"

class user
{
    string password{};

public:
    string username{};

    // intialize account with param
    user(string username_, string password_)
    {
        username = username_;
        password = password_;
    }

    // initialize account without param
    user()
    {
        username = "No name";
        password = "";
    }

    // test login, login success when name and password is correct
    bool test_login(string username_, string password_)
    {
        return (username == username_) && (password == password_);
    }

    // change password
    // old password must be correct
    // old and new password cannot be same
    // new password again must correct
    bool change_password(string old_password_, string new_password_)
    {
        // when current password is wrong
        if (old_password_ != password)
        {
            write_line("Failed to change password - invalid password");
            return false;
        }
        // password reuse
        else if (old_password_ == new_password_)
        {
            write_line("Failed to change password - password reuse");
            return false;
        }
        // password changed
        else if (old_password_ == password && old_password_ != new_password_)
        {
            password = new_password_;
            write_line("Password changed");
            return true;
        }

        // backup return
        return old_password_ == password && old_password_ != new_password_;
    }
};

int main()
{
    return 0;
}