#include "splashkit.h"
#include "utilities.h"

struct Unit_result
{
    string unit_code;
    string unit_name;
    int score;
};

Unit_result read_unit_result()
{
    Unit_result result{};

    result.unit_code = read_string("Enter a unit code: ");
    result.unit_name = read_string("Enter a unit name: ");
    result.score = read_integer("Enter your score: ");

    return result;
}

void write_unit_result(Unit_result result)
{
    write_line(result.unit_code + ", " + result.unit_name + ", " + to_string(result.score));

    if (result.score >= 80)
    {
        write_line("Congratulations");
    }
    else
    {
        write_line();
    }
}

int main()
{
    Unit_result result;

    result = read_unit_result();

    write_unit_result(result);

    return 0;
}