#include "splashkit.h"
#include "bounded_array.hpp"
#include <string>

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
};

/**
 * This constructor populates the path_data's respective fields.
 *
 * @param description_ the description of the path
 * @param destination_ the destination of the path - a pointer to the room it goes to
 */


struct room_data
{
    string title;
    string description;
};

int main()
{
    return 0;
}