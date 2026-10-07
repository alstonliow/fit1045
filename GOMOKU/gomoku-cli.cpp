#include "splashkit.h"
#include "gomoku.h"
#include <cctype>

/**
 * Gets the symbol used to draw a cell.
 *
 * @param c the cell to draw
 * @return "." for empty, "X" for Black, "O" for White
 */
string cell_symbol(cell c)
{
    switch (c)
    {
    case cell::BLACK:
        return "X";
    case cell::WHITE:
        return "O";
    default:
        return ".";
    }
}

/**
 * Gets a side's display name.
 *
 * @param s the side
 * @return "Black (X)" or "White (O)"
 */
string side_name(side s)
{
    return (s == side::BLACK) ? "Black (X)" : "White (O)";
}

/**
 * Draws the board with column letters A.. along the top and row numbers
 * 1.. down the side.
 *
 * @param b the board to draw
 */
void print_board(const board &b)
{
    string header = "   ";
    for (int c = 0; c < BOARD_SIZE; c++)
        header += string(1, (char)('A' + c)) + " ";
    write_line(header);

    for (int r = 0; r < BOARD_SIZE; r++)
    {
        string line = (r + 1 < 10 ? " " : "") + to_string(r + 1) + " ";
        for (int c = 0; c < BOARD_SIZE; c++)
            line += cell_symbol(b.cell_at(r, c)) + " ";
        write_line(line);
    }
}

/**
 * Parses a move such as "h8" into board coordinates.
 *
 * @param input the text the player typed
 * @param row   set to the 0-based row on success
 * @param col   set to the 0-based column on success
 * @return true if input is a column letter followed by a row number,
 *         otherwise false (the move may still be off the board)
 */
bool parse_move(const string &input, int &row, int &col)
{
    if (input.length() < 2 || !isalpha(input[0]))
        return false;

    string number = input.substr(1);
    if (!is_integer(number))
        return false;

    col = tolower(input[0]) - 'a';
    row = to_integer(number) - 1;
    return true;
}

/**
 * Prints the result of a finished game.
 *
 * @param state the final game state
 */
void print_result(game_state state)
{
    if (state == game_state::BLACK_WIN)
        write_line("Black (X) wins!");
    else if (state == game_state::WHITE_WIN)
        write_line("White (O) wins!");
    else
        write_line("It's a draw.");
}

int main()
{
    gomoku game;
    string input;

    write_line("Gomoku - get " + to_string(WIN_LENGTH) + " in a row to win.");
    write_line("Enter a move like h8, or u (undo), r (restart), q (quit).");

    while (true)
    {
        write_line();
        print_board(game.get_board());

        if (game.get_state() != game_state::PLAYING)
        {
            print_result(game.get_state());
            write("u (undo), r (restart), q (quit): ");
        }
        else
        {
            write(side_name(game.current_side()) + " move: ");
        }

        input = trim(read_line());
        if (input.empty())
            continue;

        char command = tolower(input[0]);
        if (input.length() == 1 && command == 'q')
            break;
        if (input.length() == 1 && command == 'u')
        {
            if (!game.undo())
                write_line("Nothing to undo.");
            continue;
        }
        if (input.length() == 1 && command == 'r')
        {
            game.reset();
            continue;
        }

        int row, col;
        if (game.get_state() != game_state::PLAYING)
            write_line("The game is over.");
        else if (!parse_move(input, row, col))
            write_line("Invalid input. Try something like h8.");
        else if (!game.place(row, col))
            write_line("You can't play there.");
    }

    write_line("Bye!");
}
