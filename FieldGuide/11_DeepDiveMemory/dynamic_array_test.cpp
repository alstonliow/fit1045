#include "splashkit.h"
#include "dynamic-array.hpp"

void test_value(double value, double expected, string fail_message)
{
    if (value != expected)
    {
        write_line(to_string(value) + " != " + to_string(expected) + " | " + fail_message);
    }
}

int main()
{
    write_line("Running tests - no output means no errors :)");

    dynamic_array<double> numbers;
    test_value(numbers.length(), 0, "0 Length failed");

    // Push past initial capacity (4) to trigger resize
    for (int i = 0; i < 5; i++)
    {
        numbers.add(i * 10);
    }
    test_value(numbers.length(), 5, "5 Length failed (resize may have failed)");
    test_value(numbers.get(0), 0, "Value survived resize failed");
    test_value(numbers.get(4), 40, "Last add after resize failed");

    // get returns a reference - test write-through
    numbers.get(0) = -8.5;
    test_value(numbers.get(0), -8.5, "Get write failed");

    // remove should shift later elements down
    numbers.remove(1);
    test_value(numbers.length(), 4, "Length after remove failed");
    test_value(numbers.get(1), 20, "Remove shift failed");

    // operator[] should match get
    numbers[0] = 999;
    test_value(numbers[0], 999, "operator[] failed");

    write_line("Tests done");

    // Copying/assignment should fail to COMPILE - uncomment to verify:
    // dynamic_array<double> copy = numbers;
}