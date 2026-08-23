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
        // password changed, return true
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
    user u{};

    int option{};

    while (option != 4)
    {
        // print the menu to user
        write_line("1: Set Account");
        write_line("2: Test Login");
        write_line("3: Change Password");
        write_line("4: Quit");

        // read option from user
        option = read_integer("Enter your option: ", 1, 4);

        // doing each case with option
        switch (option)
        {
        // Set account
        case 1:
            // add {} to crate a new space
            {
                // ask username and password
                string u_name = read_string("Username: ");
                string u_pass = read_string("Password: ");

                // set account
                u = user(u_name, u_pass);
                write_line("Account Set");

                break;
            }
        // test login
        case 2:
        {
            // ask username and password
            string u_name = read_string("Username: ");
            string u_pass = read_string("Password: ");

            // check whether login successed or failed
            if (u.test_login(u_name, u_pass))
            {
                write_line("Login Successed");
            }
            else
            {
                write_line("Login Failed");
            }
            break;
        }
        // change password
        case 3:
        {
            string old_pass = read_string("Enter current password: ");
            string new_pass = read_string("Enter new password: ");

            u.change_password(old_pass, new_pass);

            break;
        }
        case 4:
            break;
        default:
            break;
        }
    }

    return 0;
}