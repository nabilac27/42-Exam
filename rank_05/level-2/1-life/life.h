#ifndef LIFE_H
# define LIFE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int**   create_board(int width, int height);
void    free_board(int **board, int height);

void    read_input(int **board, int width, int height);
void    print_board(int **board, int width, int height);

int     count_neighbors(int **board, int width, int height, int x, int y);
int**   update_board(int **board, int width, int height);

# endif
