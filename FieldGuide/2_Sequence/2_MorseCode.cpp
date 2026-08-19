#include "splashkit.h"

int main()
{
    load_sound_effect("dit", "2_MorseSound/morse_dit.ogg");
    load_sound_effect("dah", "2_MorseSound/morse_dah.ogg");

    open_window("Morse Code Window", 800, 600);
    clear_screen(COLOR_WHITE);

    // Jame speak now
    draw_text("Jame: Hi everyone", COLOR_BLACK, 100, 100);
    refresh_screen();
    // H
    play_sound_effect("dit");
    delay(200);
    play_sound_effect("dit");
    delay(200);
    play_sound_effect("dit");
    delay(200);
    play_sound_effect("dit");
    delay(400);

    // i
    play_sound_effect("dit");
    delay(200);
    play_sound_effect("dit");
    delay(400);

    // e
    play_sound_effect("dit");
    delay(400);

    // v
    play_sound_effect("dit");
    delay(200);
    play_sound_effect("dit");
    delay(200);
    play_sound_effect("dit");
    delay(200);
    play_sound_effect("dah");
    delay(600);

    // e
    play_sound_effect("dit");
    delay(400);

    // r
    play_sound_effect("dit");
    delay(200);
    play_sound_effect("dah");
    delay(400);
    play_sound_effect("dit");
    delay(400);

    // y
    play_sound_effect("dah");
    delay(400);
    play_sound_effect("dit");
    delay(200);
    play_sound_effect("dah");
    delay(400);
    play_sound_effect("dah");
    delay(600);

    // o
    play_sound_effect("dah");
    delay(400);
    play_sound_effect("dah");
    delay(400);
    play_sound_effect("dah");
    delay(600);

    // n
    play_sound_effect("dah");
    delay(400);
    play_sound_effect("dit");
    delay(400);

    // e
    play_sound_effect("dit");
    delay(400);

    delay(1000);

    // Olivier speak now
    draw_text("Olivier: I'm good", COLOR_BLACK, 100, 200);
    refresh_screen();

    // I
    play_sound_effect("dit");
    delay(200);
    play_sound_effect("dit");
    delay(400);

    // m
    play_sound_effect("dah");
    delay(400);
    play_sound_effect("dah");
    delay(600);

    // g
    play_sound_effect("dah");
    delay(400);
    play_sound_effect("dah");
    delay(400);
    play_sound_effect("dit");
    delay(400);

    // o
    play_sound_effect("dah");
    delay(400);
    play_sound_effect("dah");
    delay(400);
    play_sound_effect("dah");
    delay(600);

    // o
    play_sound_effect("dah");
    delay(400);
    play_sound_effect("dah");
    delay(400);
    play_sound_effect("dah");
    delay(600);

    // d
    play_sound_effect("dah");
    delay(400);
    play_sound_effect("dit");
    delay(200);
    play_sound_effect("dit");
    delay(400);

    delay(1000);

    // Alex speak now
    draw_text("Alex: Me too", COLOR_BLACK, 100, 300);
    refresh_screen();

    // M
    play_sound_effect("dah");
    delay(400);
    play_sound_effect("dah");
    delay(600);

    // e
    play_sound_effect("dit");
    delay(400);

    // t
    play_sound_effect("dah");
    delay(600);

    // o
    play_sound_effect("dah");
    delay(400);
    play_sound_effect("dah");
    delay(400);
    play_sound_effect("dah");
    delay(600);

    // o
    play_sound_effect("dah");
    delay(400);
    play_sound_effect("dah");
    delay(400);
    play_sound_effect("dah");
    delay(600);

    delay(20000);

    return 0;
}