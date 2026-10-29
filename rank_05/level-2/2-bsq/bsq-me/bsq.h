#ifndef BSQ_H
# define BSQ_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* STRUCT ********************************************** */

typedef struct s_map
{
	int		rows;
	int		cols;
	char	empty;
	char	obstacle;
	char	full;
	char	**grid;
}	t_map;

/* UTILS *********************************************** */

int		is_printable(char c);
int		min3(int top, int left, int diagonal);
void	free_map(t_map *map);
void	print_map(t_map *map);

/* SOLVE BSQ ******************************************* */

void	free_dp(int **dp, int rows);
void	solve_bsq(t_map *map);

/* READ MAP ******************************************** */

int		read_grid(FILE *file_ptr, t_map *map);
int		read_header(FILE *file_ptr, t_map *map);
int		read_map(FILE *file_ptr, t_map *map);

/* PROCESS MAP ***************************************** */

void	process_map(FILE *file_ptr);

#endif