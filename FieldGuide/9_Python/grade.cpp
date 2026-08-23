#include "splashkit.h"
#include "utilities.h"
#include "splashkit-arrays.h"

class grade_analyser
{

    // define a list of a grade(empty)
    dynamic_array<int> grades{};

public:
    // add one grade data
    void add_grade(int g)
    {
        add(grades, g);
    }

    // add a list of grades
    // overload add_grade()
    // need array
    void add_grade(dynamic_array<int> g)
    {
        for (int i = 0; i < length(g); i++)
        {
            add_grade(g[i]);
        }
    }

    // another version of overload
    // no need array
    void add_grade()
    {
        int count = read_integer("How many grades? ");
        for (int i = 0; i < count; i++)
        {
            int g = read_integer("Enter grade " + to_string(i + 1) + ": ");
            add_grade(g);
        }
    }

    // average
    double average()
    {
        double total{};
        for (int i = 0; i < length(grades); i++)
        {
            total += grades[i];
        }
        return total / length(grades);
    }

    // pass rate
    double pass_rate()
    {
        // the num of student grades >= 50
        int num_pass{};
        for (int i = 0; i < length(grades); i++)
        {
            if (grades[i] >= 50)
            {
                num_pass++;
            }
        }
        return (double)num_pass / length(grades) * 100;
    }

    // return the number of student is hd
    int num_hd()
    {
        int n_hd{};
        for (int i = 0; i < length(grades); i++)
        {
            if (grades[i] >= 80)
            {
                n_hd++;
            }
        }
        return n_hd;
    }
};

int main()
{
    grade_analyser analyser;

    // Let the user enter a list of grades
    analyser.add_grade();

    // Output the results
    write_line("Average: " + to_string(analyser.average()));
    write_line("Pass rate: " + to_string(analyser.pass_rate() * 100) + "%");
    write_line("High distinctions: " + to_string(analyser.num_hd()));

    return 0;
}