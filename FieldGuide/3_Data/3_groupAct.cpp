#include "splashkit.h"

int main()
{
    double tax_rate = 703.0;
    double student_age;
    double course_grade;
    string password;
    string error_message;
    double total_price;
    double shipping_cost;
    double discount_percent = 2.54;
    double max_capacity;

    write_line("Enter your weight in pounds:");
    password = read_line();
    student_age = to_double(password);

    write_line("Enter your height in inches:");
    password = read_line();
    course_grade = to_double(password);

    // pow is a build-in C++
    max_capacity = pow(course_grade, 2.0);

    total_price = (student_age * tax_rate) / max_capacity;

    write_line();
    write_line("===== Results =====");
    write_line("Weight: " + to_string(student_age) + " lbs");
    write_line("Height: " + to_string(course_grade) + " inches");
    write_line("BMI Score: " + to_string(total_price, 1));
    write_line();

    double inventory_count = student_age / 2.205;
    double monthly_fee = course_grade * discount_percent / 100.0;
    double annual_revenue = inventory_count / pow(monthly_fee, 2);
    double bonus_amount = round(annual_revenue * 10.0) / 10.0;

    write_line("Metric Conversion:");
    write_line("Weight: " + to_string(inventory_count, 1) + " kg");
    write_line("Height: " + to_string(monthly_fee, 2) + " m");
    write_line("BMI Score: " + to_string(bonus_amount, 1));
}