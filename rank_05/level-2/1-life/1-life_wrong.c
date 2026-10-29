
#include "life.h"


int **create_board(int width, int height)
{
    int **board;
    int y;

    board = calloc(height, sizeof(int *)); // height!!
    y     = 0;

    if (!board)
        return (NULL);

    while (y < height)
    {
        board[y] = calloc(width, sizeof(int)); // width !!

        if (!board[y])
        {
            // ❌ BUG 3: Must free all previous rows,
            // not just the outer pointer.
            free_board(board, height);
            return(NULL);
        }
        y++;
    }
    return (board);
}


void free_board(int **board, int height)
{
    int y;

    y = 0;

    if (!board)
        return;
    while (y < height)
    {
        free(board[y]);
        y++;
    }
    free(board);
}


void read_input(int **board, int width, int height)
{
    int     x, y, draw;
    char    command; // CHAR command!

    x    = 0;
    y    = 0;
    draw = 0;

    while (read(0, &command, 1) > 0)
    {
        if (command == 'x') // X FIRST!
            draw = !draw;
        // ❌ BUG: y >= 0 allows y to become -1.
        else if (command == 'w' && y > 0)
            y--;
        else if (command == 's' && y < height - 1)
            y++;
        // ❌ BUG: x >= 0 allows x to become -1.
        else if (command == 'a' && x > 0)
            x--;
        else if (command == 'd' && x < width - 1)
            x++;
        if (draw)
            board[y][x] = 1;
    }
}

void print_board(int **board, int width, int height)
{
    int y, x;

    y = 0;
    while (y < height)
    {
        x = 0;
        while (x < width)
        {
            if (board[y][x])
                putchar('0');
            else
                putchar(' ');
            x++;
        }
        putchar('\n');
        y++;
    }
}

int count_neigh(int **board, int width, int height, int x, int y)
{
    int y_offset, x_offset, neigh_y, neigh_x, count;

    y_offset = -1;
    count    = 0;

    // ❌ BUG 1: Excludes offset +1.
    while (y_offset <= 1)
    {
        x_offset = -1;

        // ❌ BUG 2: Excludes offset +1.
        while (x_offset <= 1)
        {
            if (y_offset != 0 || x_offset != 0)
            {
                neigh_y = y + y_offset;
                neigh_x = x + x_offset;

                // 
                if (neigh_y >= 0     && 
                    neigh_y < height &&
                    neigh_x >= 0     &&
                    neigh_x < width  &&
                    board[neigh_y][neigh_x])
                    count++;
            }
            x_offset++;
        }
        y_offset++;
    }
    return (count);
}


int **update_board(int **board, int height, int width)
{
    int **new_board;
    int y, x, neigh; // y, x neigh!!

    new_board = create_board(width, height); // NEW_BOARD = CREATE_BOARD
    if (!new_board)
        return (board);

    y = 0;
    while (y < height)
    {
        x = 0;
        while (x < width)
        {
            neigh = count_neigh(board, width, height, x, y); // NEIGH = COUNT_NEIGH INSIDE X
            if (board[y][x] && (neigh == 2 || neigh == 3))
                new_board[y][x] = 1;
            else if (!board[y][x] && neigh == 3)
                new_board[y][x] = 1;
            x++;
        }
        y++;
    }
    free_board(board, height); // FREE_BOARD!!
    return (new_board);
}

int main(int argc, char **argv)
{
    int     width, height, iter, curr_iter;
    int**   board;

    if (argc != 4)
        return (1);

    width   = atoi(argv[1]);
    height  = atoi(argv[2]);
    iter    = atoi(argv[3]);

    if (width <= 0 || height <= 0 || iter < 0)
        return (1);

    board = create_board(width, height);
    if (!board)
        return (1);

    read_input(board, width, height);

    curr_iter = 0;
    while (curr_iter < iter)
    {
        board = update_board(board, height, width); // BOARD = UDPATE_BOARD !
        curr_iter++;
    }

    print_board(board, width, height);
    free_board(board, height);      // FREE_BOARD !

    return (0);
}

