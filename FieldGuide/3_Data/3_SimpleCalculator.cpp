#include "splashkit.h"

const int MINUTES_PER_HOUR = 60;

int main()
{
    string name{};
    string user_input{};
    double distance{}, time{}, speed{};
    double remaining_distance{}, total_distance{};
    double time_to_destination{}, total_time{};

    // input name
    write("Enter your name: ");
    name = read_line();

    // output name
    write_line();
    write_line("Hi " + name + ".");
    write_line();

    // input km
    write("How far have you travelled so far? Enter km: ");
    user_input = read_line();
    distance = to_double(user_input);

    // input time
    write("How long has it taken? Enter minutes: ");
    user_input = read_line();
    time = to_double(user_input);

    // calculate speed
    speed = distance / (time / MINUTES_PER_HOUR);

    write_line();
    write_line("Your speed is " + to_string(speed) + " km/h");
    write_line();

    write("How far do you have to go? Enter km: ");
    user_input = read_line();
    remaining_distance = to_double(user_input);

    time_to_destination = remaining_distance / speed * MINUTES_PER_HOUR;

    write_line("You will take another " + to_string(time_to_destination) + "minutes before you arrived.");

    total_distance = distance + remaining_distance;
    total_time = time + time_to_destination;

    write_line("Your total distance will be " + to_string(total_distance) + "km");
    write_line("Your total time is " + to_string(total_time) + "minutes");

    return 0;
}