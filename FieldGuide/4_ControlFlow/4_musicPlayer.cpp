#include "splashkit.h"

int main()
{
    string user_input, name, path, check_name;
    int option, times;

    write_line("Welcome to my simple music player");

    do
    {
        write_line("1: Load song");
        write_line("2: Play song");
        write_line("3: Stop song");
        write_line("4: Quit");

        // get user option
        write("Option: ");
        user_input = read_line();
        option = to_integer(user_input);

        switch (option)
        {
            // Load song
        case 1:
            write("What is the name of the song: ");
            user_input = read_line();
            name = user_input;

            write("Path to the file: ");
            user_input = read_line();
            path = user_input;

            load_music(name, path);

            // load when can success the path
            if (has_music(name))
            {
                write_line("Loading " + path + " passed!");
            }

            else
            {
                write_line("Loading " + path + " failed!");
            }

            break;
            // play song
        case 2:
            write("What is the name of the song: ");
            user_input = read_line();
            check_name = user_input;

            // play when it can work
            if (has_music(check_name))
            {
                write("How many times you want to play? Enter a integer: ");
                user_input = read_line();
                times = to_integer(user_input);

                write_line("(music start playing)");
                play_music(check_name, times);
            }

            else
            {
                write_line("There is nothing called '" + check_name + "' loaded");
            }

            break;
            // stop song
        case 3:
            if (has_music(check_name))
            {
                music_paused();
            }

            else
            {
                write_line("No music is playing");
            }

            break;
            // quit
        case 4:
            write_line("bye");
            break;
        default:
            write_line("Invalid option");
            break;
        }
    } while (option != 4); // quit when enter 4
}