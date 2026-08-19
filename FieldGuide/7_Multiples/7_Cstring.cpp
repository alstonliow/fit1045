#include "splashkit.h"

// Concatenation

const int FULL_NAME_LEN = 50;

int main(void)
{
    char first_name[] = "Alston";
    char last_name[] = "Liow";
    char full_name[FULL_NAME_LEN];

    // copy the first name into the full name, character by character
    int i = 0;
    while (first_name[i] != '\0')
    {
        full_name[i] = first_name[i];
        i++;
    }

    // add a space to the full name
    // using i++ here is a clever way to first read the value of i,
    // and then increment it as we need it later on.
    full_name[i++] = ' ';

    // Assign each letter of last name to the end of the full name
    int j = 0;
    while (last_name[j] != '\0')
    {
        full_name[i + j] = last_name[j];
        j++;
    }

    // don't forget the null terminator!
    full_name[j + i] = '\0';

    write_line(full_name);

    return 0;
}