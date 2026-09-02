#include "splashkit.h"

const int CURRENT_YEAR = 2026;

int find_negative(int number)
{
    if (number < 0)
    {
        return number;
    }

    return 0;
}

int find_adult_age(int birth_year)
{
    if (CURRENT_YEAR - birth_year)
    {
        return CURRENT_YEAR - birth_year;
    }
    else
    {
        write_line("No adult");
    }

    return 0;
}

int main()
{
    write_line(find_negative(-1));

    write_line(find_adult_age(1990));

    write_line(find_adult_age(2015));

    return 0;
}