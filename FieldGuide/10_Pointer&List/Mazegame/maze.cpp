#include "splashkit.h"
#include "bounded_array.hpp"
#include <string>
#include "utilities.h"

// Forward declare room_data - the compiler
// knows this struct exists now, it
// just doesn't know what it consists of yet
struct room_data;

// Also set up a type alias
typedef room_data *room_ptr;

struct path_data
{
    string description;
    room_ptr destination;

    path_data() {};

    /**
     * This constructor populates the path_data's respective fields.
     *
     * @param description_ the description of the path
     * @param destination_ the destination of the path - a pointer to the room it goes to
     */
    path_data(string description_, room_ptr destination_)
    {
        description = description_;
        destination = destination_;
    }

    /**
     * Outputs the path's description to the terminal. Showing the index of the path
     * and the description, but no details of where it goes.
     *
     * @param idx   the index of the path - used to select it from the list
     */
    void print_path(int idx)
    {
        write_line(to_string(idx) + " - " + description);
    }
};

struct room_data
{
    string title;
    string description;

    /**
     * This constructor populates the room_data's respective fields.
     *
     * @param title_         The title of the room
     * @param description_   The description of the room
     */
    room_data(string title_, string description_)
    {
        title = title_;
        description = description_;
    }

    /**
     * Output the room's title and description to the terminal.
     */
    void print_room()
    {
        write_line(title);
        write_line("---------");
        write_line(description);

        if (paths.length() > 0)
        {
            write_line("There are paths leading:");
            for (int i = 0; i < paths.length(); i++)
            {
                paths[i].print_path(i);
            }
        }
    }
};

/**
 * Move the player through the selected path, setting the player's current room
 * to the destination of the path.
 *
 * @param current_room a reference to the player's current room (a pointer to the room_data)
 * @param path a constant reference to the path to move through
 */
//...
void move_player(room_ptr &current_room, const path_data &path)
{
    current_room = path.destination;
}

int main()
{

    // ---- Set up the rooms ----
    room_data r1 = room_data("Room 1", "You are in a happy place");
    room_data r2 = room_data("Room 2", "This is room 2");
    room_data r3 = room_data("Room 3", "This is room 3");

    // ---- Create some paths ----
    // Both paths start conceptually "from" room 1 - we'll offer them to the player below
    path_data p1 = path_data("A large sliding door", &r2);
    path_data p2 = path_data("An open corridor", &r3);

    // ---- Get current room to point to room 1 ----
    room_ptr current_room = &r1;

    // ---- Show the user the room they are in (current room) ----
    current_room->print_room();

    // ---- Show them the paths we set up ----
    write_line("There are paths leading:");
    p1.print_path(0);
    p2.print_path(1);

    // ---- Ask which path they want to take ----
    int option = read_integer("Which path do you want to take? ");

    while (option != 0 && option != 1)
    {
        write_line("Choose 0 or 1");
        option = read_integer("Option: ");
    }

    // ---- Move them through that path ----
    if (option == 0)
    {
        move_player(current_room, p1);
    }
    else
    {
        move_player(current_room, p2);
    }

    // ---- Print the details of the room they are in (using the current room) ----
    write_line("");
    write_line("You have moved. Your new location:");
    current_room->print_room();

    return 0;
}