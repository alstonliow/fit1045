#include "splashkit.h"

int main()
{
    string user_input{};
    string path{}, name{};
    double seconds{}, initial_volume{}, repeat_volume{};
    int times{};

    write_line("Welcome to the music play test.");

    write_line("What file would you like to load? Enter path: ");
    user_input = read_line();
    path = user_input;

    write_line("What do I call this music? Enter name: ");
    user_input = read_line();
    name = user_input;

    write_line("Loading " + name + " from " + path);
    load_sound_effect(name, path);

    // details
    write_line("How long do you want to play it for? Enter seconds: ");
    user_input = read_line();
    seconds = to_double(user_input);
    times = seconds / 6;

    write_line("At what initial percent? Enter volume (0 to 1): ");
    user_input = read_line();
    initial_volume = to_double(user_input);

    write_line("At what repeat percent? Enter volume (0 to 1): ");
    user_input = read_line();
    repeat_volume = to_double(user_input);

    // play music
    write_line("Playing " + name + " at " + to_string(initial_volume) + " for " + to_string(seconds) + " seconds...");
    play_sound_effect(name, times, initial_volume);
    delay(seconds * 1000);
    write_line("Stopping music");

    write_line("Playing " + name + " at " + to_string(repeat_volume) + " for " + to_string(seconds) + " seconds...");
    play_sound_effect(name, times, repeat_volume);
    delay(seconds * 1000);
    write_line("Stopping music");

    return 0;
}