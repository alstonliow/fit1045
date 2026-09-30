#include <cstdlib>
#include "splashkit.h"
#include "utilities.h"

int main()
{
    // declare pointer and size
    double *data_ptr;
    int size;

    // read size, allocate space on the heap by the size
    size = read_integer("Enter the number of items to store: ");
    data_ptr = (double *)malloc(size * sizeof(double));

    // check the memory could be allocate
    if (data_ptr == NULL)
    {
        write_line("Memory allocation failed");
        return 1;
    }

    // Populate the data, asssigning the value to each element on the array
    for (int i = 0; i < size; i++)
    {
        data_ptr[i] = read_double("Enter a number: ");
    }

    // Access the value
    for (int i = 0; i < size; i++)
    {
        write_line("Value at index " + to_string(i) + ":" + to_string(data_ptr[i]));
    }

    free(data_ptr);
    data_ptr = nullptr;

    return 0;
}