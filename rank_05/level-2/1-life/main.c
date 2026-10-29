#include "life.h"

int**   create_board(int width, int height)
{
    int**   board;
    int     y;

    board = calloc(height, sizeof(int *));
    if (!board)
        return (NULL);

    y = 0;
    while (y < height)
    {
        board[y] = calloc(width, sizeof(int));
        if (!board[y])
        {
            free_board(board, height);
            return (NULL);
        }
        y++;
    }
    return (board);
}

void    free_board(int **board, int height)
{
    int y;

    y = 0;
    if (!board)
        return ;
    while(y < height)
    {
        free(board[y]);
        y++;
    }
    free(board);
}

void    read_input(int **board, int width, int height)
{
    int     y, x, draw;
    char    command;

    y    = 0;
    x    = 0;
    draw = 0;
    
    while (read(0, &command, 1) > 0)
    {
        if (command == 'x')
            draw = !draw;
        else if (command == 'w' && y > 0)
            y--;
        else if (command == 's' && (y < height - 1))
            y++;
        else if (command == 'a' && x > 0)
            x--;
        else if (command == 'd' && (x < width - 1))
            x++;
        if (draw)
            board[y][x] = 1;
    }
}

void    print_board(int **board, int width, int height)
{
    int     y, x;

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

int     count_neighbors(int **board, int width, int height, int x, int y)
{
    int     y_offset, x_offset, neighbor_y, neighbor_x, count;

    count     = 0;
    y_offset  = -1;
    while (y_offset <= 1)
    {
        x_offset = -1;
        while (x_offset <= 1)
        {
            if (y_offset != 0 || x_offset != 0)
            {
                neighbor_y = y + y_offset;
                neighbor_x = x + x_offset;
                if (neighbor_y >= 0 &&
                    neighbor_y < height &&
                    neighbor_x >= 0 &&
                    neighbor_x < width &&
                    board[neighbor_y][neighbor_x])
                    count++;
            }
            x_offset++;
        }
        y_offset++;
    }
    return (count);
}

int**   update_board(int **board, int width, int height)
{
    int**   new_board;
    int     y, x, neighbors;

    new_board = create_board(width, height);
    if (!new_board)
        return (board);

    y = 0;
    while (y < height)
    {
        x = 0;
        while (x < width)
        {
            neighbors = count_neighbors(board, width, height, x, y);
            if (board[y][x] && (neighbors == 2 || neighbors == 3))
                new_board[y][x] = 1;
            else if (!board[y][x] && (neighbors == 3))
                new_board[y][x] = 1;
            x++;
        }
        y++;
    }
    free_board(board, height);
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
        board = update_board(board, width, height);
        curr_iter++;
    }
    print_board(board, width, height);
    free_board(board, height);
    return (0);
}
