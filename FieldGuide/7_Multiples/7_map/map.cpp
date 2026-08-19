#include "splashkit.h"
#include "utilities.h"
#include "splashkit-arrays.h"

const int MAX_MAP_ROWS = 50;
const int MAX_MAP_COLS = 50;
const int TILE_WIDTH = 30;
const int TILE_HEIGHT = 30;
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int NUM_OF_TILE_KIND = 4;

enum tile_kind
{
    WATER_TILE,
    GRASS_TILE,
    DIRT_TILE,
    SAND_TILE
};

enum explorer_state_kind
{
    PLAY_STATE,
    EDIT_STATE
};

struct tile_data
{
    tile_kind kind{};
};

struct map_data
{
    tile_data tiles[MAX_MAP_COLS][MAX_MAP_ROWS]{}; // cols, rows
};

struct editor_data
{
    tile_kind editor_tile_kind{GRASS_TILE};
};

struct explorer_data
{
    map_data map{};
    explorer_state_kind state{PLAY_STATE};
    editor_data editor{};
    // camera start from middle of screen
    point_2d camera_position{
        (double)(MAX_MAP_COLS * TILE_WIDTH) / 2 - WINDOW_WIDTH / 2,
        (double)(MAX_MAP_ROWS * TILE_HEIGHT) / 2 - WINDOW_HEIGHT / 2};
};

struct player_data
{
    bitmap bmp{};
    point_2d player_pos{};
    double size{};
    int speed{2};
};

// initial the map with all GRASS
void init_map_data(map_data &map)
{
    for (int c = 0; c < MAX_MAP_COLS; c++)
    {
        for (int r = 0; r < MAX_MAP_ROWS; r++)
        {
            map.tiles[c][r].kind = GRASS_TILE;
        }
    }
}

void init_explorer_data(explorer_data &data)
{
    init_map_data(data.map);
}

/**
 * Returns the color for the indicated tile kind.
 *
 * @param kind the tile kind to get the color for
 * @return color the color for the tile kind
 */
color color_for_tile_kind(tile_kind kind)
{
    switch (kind)
    {
    case WATER_TILE:
        return COLOR_BLUE;
    case GRASS_TILE:
        return COLOR_LAWN_GREEN;
    case SAND_TILE:
        return COLOR_BLANCHED_ALMOND;
    case DIRT_TILE:
        return COLOR_ROSY_BROWN;
    default:
        return COLOR_WHITE;
    }
}

/**
 * Draw a tile at the indicated location.
 *
 * @param tile the tile to draw, passed by constant reference
 * @param x the x location of the top left of the tile
 * @param y the y location of the top left of the tile
 */
void draw_tile(const tile_data &tile, double x, double y)
{
    fill_rectangle(color_for_tile_kind(tile.kind), x, y, TILE_WIDTH, TILE_HEIGHT);
}

// draw the map with position
void draw_map(const map_data &map)
{
    for (int c = 0; c < MAX_MAP_COLS; c++)
    {
        for (int r = 0; r < MAX_MAP_ROWS; r++)
        {
            draw_tile(map.tiles[c][r], c * TILE_WIDTH, r * TILE_HEIGHT);
        }
    }
}

// random the map
void random_map(map_data &map)
{
    for (int c = 0; c < MAX_MAP_COLS; c++)
    {
        for (int r = 0; r < MAX_MAP_ROWS; r++)
        {
            map.tiles[c][r].kind = (tile_kind)rnd(NUM_OF_TILE_KIND);
        }
    }
}

/**
 * Shift + E to enter edit mode, ESC to exit
 *
 * In edit mode, type R to random map
 */
void handle_input(explorer_data &data)
{
    if (key_typed(E_KEY) && (key_down(LEFT_SHIFT_KEY) || key_down(RIGHT_SHIFT_KEY)))
    {
        data.state = EDIT_STATE;
    }

    // in edit state
    if (data.state == EDIT_STATE)
    {
        if (key_typed(ESCAPE_KEY))
        {
            data.state = PLAY_STATE;
        }
        if (key_down(R_KEY))
        {
            random_map(data.map);
        }

        // changing the tile using number 1 to 4
        if (key_typed(NUM_1_KEY))
        {
            data.editor.editor_tile_kind = WATER_TILE;
        }
        if (key_typed(NUM_2_KEY))
        {
            data.editor.editor_tile_kind = GRASS_TILE;
        }
        if (key_typed(NUM_3_KEY))
        {
            data.editor.editor_tile_kind = DIRT_TILE;
        }
        if (key_typed(NUM_4_KEY))
        {
            data.editor.editor_tile_kind = SAND_TILE;
        }

        // using mouse to draw
        if (mouse_down(LEFT_BUTTON))
        {
            point_2d mouse_pos = mouse_position();
            int c = (int)((mouse_pos.x + data.camera_position.x) / TILE_WIDTH);
            int r = (int)((mouse_pos.y + data.camera_position.y) / TILE_HEIGHT);

            if (c >= 0 && c < MAX_MAP_COLS && r >= 0 && r < MAX_MAP_ROWS)
            {
                data.map.tiles[c][r].kind = data.editor.editor_tile_kind;
            }
        }
    }

    // move camera
    if (key_down(LEFT_KEY))
    {
        data.camera_position.x -= 1;
    }
    if (key_down(RIGHT_KEY))
    {
        data.camera_position.x += 1;
    }
    if (key_down(UP_KEY))
    {
        data.camera_position.y -= 1;
    }
    if (key_down(DOWN_KEY))
    {
        data.camera_position.y += 1;
    }

    // restrict camera area inside the map
    if (data.camera_position.x < 0)
    {
        data.camera_position.x = 0;
    }
    if (data.camera_position.x > MAX_MAP_COLS * TILE_WIDTH - WINDOW_WIDTH)
    {
        data.camera_position.x = MAX_MAP_COLS * TILE_WIDTH - WINDOW_WIDTH;
    }
    if (data.camera_position.y < 0)
    {
        data.camera_position.y = 0;
    }
    if (data.camera_position.y > MAX_MAP_ROWS * TILE_HEIGHT - WINDOW_HEIGHT)
    {
        data.camera_position.y = MAX_MAP_ROWS * TILE_HEIGHT - WINDOW_HEIGHT;
    }
}

void draw_explorer(const explorer_data &data)
{
    set_camera_position(data.camera_position);

    clear_screen(COLOR_WHITE);
    draw_map(data.map);

    if (data.state == EDIT_STATE)
    {
        draw_text("Editor", COLOR_BLACK, 0, 0, option_to_screen());

        // show now tile
        fill_rectangle(COLOR_WHITE, 0, 20, 70, 30, option_to_screen());
        fill_rectangle(color_for_tile_kind(data.editor.editor_tile_kind), 5, 25, 20, 20, option_to_screen());
        draw_text("Kind: " + to_string((int)data.editor.editor_tile_kind + 1), COLOR_BLACK, 30, 25, option_to_screen());
    }
    else
    {
        draw_text("Playing - Shift E to edit", COLOR_BLACK, 0, 0, option_to_screen());
    }

    refresh_screen();
}

int main()
{
    open_window("Map Explorer", WINDOW_WIDTH, WINDOW_HEIGHT);

    explorer_data explorer{};
    init_explorer_data(explorer);

    while (!quit_requested())
    {
        draw_explorer(explorer);
        process_events();
        handle_input(explorer);
    }

    return 0;
}