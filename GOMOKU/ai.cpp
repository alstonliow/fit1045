#include "ai.h"
#include "game_rules.h"
#include "splashkit-arrays.h"

/** Score of a won game; deeper wins score higher so faster wins are preferred. */
const int WIN_SCORE = 10000000;

/** Larger than any score, used as the starting alpha/beta. */
const int INF_SCORE = 100000000;

/** Candidates must be within this many cells of an existing stone. */
const int NEIGHBOUR_RADIUS = 2;

/** The four line directions; the other four are their opposites. */
const int LINE_COUNT = 4;
const direction LINE_DIRS[LINE_COUNT] = {direction::E, direction::SE, direction::S, direction::SW};

/** A move to consider, with a quick guess at how good it is. */
struct candidate
{
    int row;
    int col;
    int score;
};

/** The moves to try at one step of the search. */
struct candidate_list
{
    fixed_array<candidate, BOARD_SIZE * BOARD_SIZE> items;
    int count;
};

/** Settings and counters shared by every step of one search. */
struct search_context
{
    eval_weights weights;
    int max_candidates;
    bool use_pruning;
    long nodes;
};

ai_settings default_ai_settings()
{
    ai_settings s;
    s.depth = 3;
    s.max_candidates = 12;
    s.use_pruning = true;
    s.weights.five = 100000;
    s.weights.open_four = 10000;
    s.weights.closed_four = 1000;
    s.weights.open_three = 1000;
    s.weights.closed_three = 100;
    s.weights.open_two = 100;
    s.weights.closed_two = 10;
    return s;
}

/**
 * Checks whether a cell is on the board and empty.
 *
 * @param b   the board
 * @param row the row to check
 * @param col the column to check
 * @return 1 if the cell is empty, otherwise 0
 */
static int open_end(const board &b, int row, int col)
{
    return (b.in_bounds(row, col) && b.is_empty(row, col)) ? 1 : 0;
}

/**
 * Scores one line of stones.
 *
 * @param count     the number of stones in a row
 * @param open_ends how many ends are empty, 0 to 2
 * @param w         the score of each kind of line
 * @return the score; a line blocked at both ends scores 0
 */
static int pattern_score(int count, int open_ends, const eval_weights &w)
{
    if (count >= WIN_LENGTH)
        return w.five;
    if (open_ends == 0)
        return 0;

    bool both = (open_ends == 2);
    if (count == 4)
        return both ? w.open_four : w.closed_four;
    if (count == 3)
        return both ? w.open_three : w.closed_three;
    if (count == 2)
        return both ? w.open_two : w.closed_two;
    return 0;
}

/**
 * Scores the whole line of colour c that passes through a stone.
 *
 * @param b   the board
 * @param row the row of a stone of colour c
 * @param col the column of that stone
 * @param d   the line direction
 * @param c   the stone colour
 * @param w   the score of each kind of line
 * @return the score of that line
 */
static int line_score(const board &b, int row, int col, direction d, cell c, const eval_weights &w)
{
    int dr = step_row(d);
    int dc = step_col(d);
    int ahead = b.run_length(row, col, d, c);
    int behind = b.run_length(row, col, opposite(d), c);

    int open_ends = open_end(b, row + (ahead + 1) * dr, col + (ahead + 1) * dc) +
                    open_end(b, row - (behind + 1) * dr, col - (behind + 1) * dc);

    return pattern_score(1 + ahead + behind, open_ends, w);
}

/**
 * Adds up every line of one colour. Each line is scored once, from its
 * first stone.
 *
 * @param b the board
 * @param c the colour to score
 * @param w the score of each kind of line
 * @return the total score for colour c
 */
static int side_score(const board &b, cell c, const eval_weights &w)
{
    int total = 0;

    for (int r = 0; r < BOARD_SIZE; r++)
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (b.cell_at(r, col) != c)
                continue;

            for (int line = 0; line < LINE_COUNT; line++)
            {
                direction d = LINE_DIRS[line];
                int prev_row = r - step_row(d);
                int prev_col = col - step_col(d);
                if (b.in_bounds(prev_row, prev_col) && b.cell_at(prev_row, prev_col) == c)
                    continue; // not the first stone of this line

                total += line_score(b, r, col, d, c, w);
            }
        }
    return total;
}

int evaluate_board(const board &b, side me, const eval_weights &w)
{
    return side_score(b, cell_of(me), w) - side_score(b, cell_of(opponent(me)), w);
}

/**
 * Scores what a stone of colour c would do at an empty cell. The stone is
 * placed and removed again, so the board is unchanged afterwards.
 *
 * @param b   the board, with (row, col) empty
 * @param row the row to try
 * @param col the column to try
 * @param c   the colour of the stone to try
 * @param w   the score of each kind of line
 * @return the total score of the four lines through that cell
 */
static int point_score(board &b, int row, int col, cell c, const eval_weights &w)
{
    b.set_cell(row, col, c);

    int total = 0;
    for (int line = 0; line < LINE_COUNT; line++)
        total += line_score(b, row, col, LINE_DIRS[line], c, w);

    b.set_cell(row, col, cell::EMPTY);
    return total;
}

/**
 * Adds a candidate to a list.
 *
 * @param list  the list to add to
 * @param row   the row of the move
 * @param col   the column of the move
 * @param score the quick guess at how good the move is
 */
static void add_candidate(candidate_list &list, int row, int col, int score)
{
    candidate c;
    c.row = row;
    c.col = col;
    c.score = score;
    list.items[list.count] = c;
    list.count++;
}

/**
 * Keeps only the highest scoring candidates, best first.
 *
 * @param list the list to shorten
 * @param keep the most candidates to keep
 */
static void keep_best(candidate_list &list, int keep)
{
    int limit = (keep < list.count) ? keep : list.count;

    for (int i = 0; i < limit; i++)
    {
        int best = i;
        for (int j = i + 1; j < list.count; j++)
            if (list.items[j].score > list.items[best].score)
                best = j;

        candidate temp = list.items[i];
        list.items[i] = list.items[best];
        list.items[best] = temp;
    }
    list.count = limit;
}

/**
 * Lists the moves worth trying: empty cells near existing stones, best
 * first. Good moves come first so alpha-beta can skip the rest sooner.
 *
 * @param b       the board (changed during scoring but restored)
 * @param to_move the side about to move
 * @param ctx     the search settings
 * @return up to ctx.max_candidates moves, or the centre if the board is empty
 */
static candidate_list generate_candidates(board &b, side to_move, const search_context &ctx)
{
    candidate_list list;
    list.count = 0;

    fixed_array<fixed_array<bool, BOARD_SIZE>, BOARD_SIZE> nearby;
    for (int r = 0; r < BOARD_SIZE; r++)
        fill(nearby[r], false);

    bool any_stone = false;
    for (int r = 0; r < BOARD_SIZE; r++)
        for (int c = 0; c < BOARD_SIZE; c++)
        {
            if (b.is_empty(r, c))
                continue;

            any_stone = true;
            for (int dr = -NEIGHBOUR_RADIUS; dr <= NEIGHBOUR_RADIUS; dr++)
                for (int dc = -NEIGHBOUR_RADIUS; dc <= NEIGHBOUR_RADIUS; dc++)
                    if (b.in_bounds(r + dr, c + dc))
                        nearby[r + dr][c + dc] = true;
        }

    if (!any_stone)
    {
        add_candidate(list, BOARD_SIZE / 2, BOARD_SIZE / 2, 0);
        return list;
    }

    cell mine = cell_of(to_move);
    cell theirs = cell_of(opponent(to_move));

    for (int r = 0; r < BOARD_SIZE; r++)
        for (int c = 0; c < BOARD_SIZE; c++)
            if (nearby[r][c] && b.is_empty(r, c))
            {
                // Making my own lines counts double; blocking theirs counts once.
                int score = 2 * point_score(b, r, c, mine, ctx.weights) + point_score(b, r, c, theirs, ctx.weights);
                add_candidate(list, r, c, score);
            }

    keep_best(list, ctx.max_candidates);
    return list;
}

/**
 * Searches ahead from a position, assuming both sides play their best.
 *
 * @param b       the board (changed during the search but restored)
 * @param to_move the side about to move
 * @param me      the side the scores are for
 * @param depth   how many more moves to look ahead
 * @param alpha   the best score I can already guarantee
 * @param beta    the best score the opponent can already guarantee
 * @param ctx     the search settings and counters
 * @return the score of the position for me
 */
static int minimax(board &b, side to_move, side me, int depth, int alpha, int beta, search_context &ctx)
{
    ctx.nodes++;

    if (depth == 0)
        return evaluate_board(b, me, ctx.weights);

    candidate_list moves = generate_candidates(b, to_move, ctx);
    if (moves.count == 0)
        return 0; // board full: a draw

    bool maximising = (to_move == me);
    int best = maximising ? -INF_SCORE : INF_SCORE;

    for (int i = 0; i < moves.count; i++)
    {
        int row = moves.items[i].row;
        int col = moves.items[i].col;

        b.set_cell(row, col, cell_of(to_move));

        int score;
        if (check_win(b, row, col))
            score = maximising ? WIN_SCORE + depth : -(WIN_SCORE + depth);
        else
            score = minimax(b, opponent(to_move), me, depth - 1, alpha, beta, ctx);

        b.set_cell(row, col, cell::EMPTY);

        if (maximising)
        {
            if (score > best)
                best = score;
            if (best > alpha)
                alpha = best;
        }
        else
        {
            if (score < best)
                best = score;
            if (best < beta)
                beta = best;
        }

        if (ctx.use_pruning && alpha >= beta)
            break;
    }
    return best;
}

/**
 * Copies every cell from one board to another.
 *
 * @param from the board to copy
 * @param to   the board to overwrite
 */
static void copy_cells(const board &from, board &to)
{
    for (int r = 0; r < BOARD_SIZE; r++)
        for (int c = 0; c < BOARD_SIZE; c++)
            to.set_cell(r, c, from.cell_at(r, c));
}

search_result choose_placement(const board &source, side me, const ai_settings &settings)
{
    board work;
    copy_cells(source, work);

    search_context ctx;
    ctx.weights = settings.weights;
    ctx.max_candidates = settings.max_candidates;
    ctx.use_pruning = settings.use_pruning;
    ctx.nodes = 0;

    int depth = (settings.depth < 1) ? 1 : settings.depth;

    search_result result;
    result.found = false;
    result.best.row = 0;
    result.best.col = 0;
    result.best.owner = me;
    result.score = -INF_SCORE;

    candidate_list moves = generate_candidates(work, me, ctx);
    int alpha = -INF_SCORE;

    for (int i = 0; i < moves.count; i++)
    {
        int row = moves.items[i].row;
        int col = moves.items[i].col;

        work.set_cell(row, col, cell_of(me));

        int score;
        if (check_win(work, row, col))
            score = WIN_SCORE + depth;
        else
            score = minimax(work, opponent(me), me, depth - 1, alpha, INF_SCORE, ctx);

        work.set_cell(row, col, cell::EMPTY);

        if (!result.found || score > result.score)
        {
            result.found = true;
            result.score = score;
            result.best.row = row;
            result.best.col = col;
        }
        if (ctx.use_pruning && score > alpha)
            alpha = score;
    }

    result.nodes = ctx.nodes;
    return result;
}
