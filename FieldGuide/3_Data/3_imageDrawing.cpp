#include "splashkit.h"

const string IMAGE_NAME = "tree";

int main()
{
    double rotation{};
    string user_input{};
    bitmap tree;

    tree = load_bitmap("tree", "image/tree.png");

    write("Enter rotation degree: ");
    user_input = read_line();
    rotation = to_double(user_input);

    open_window("Image drawing", 500, 300);

    draw_bitmap(tree, 10, 20);
    draw_bitmap(IMAGE_NAME, 220, 20, option_rotate_bmp(rotation));

    refresh_screen();
    
    delay(10000);

    return 0;
}