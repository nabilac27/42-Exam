#include "bsq.h"

/* UTILS *********************************************** */

int	is_printable(char c)
{
	return (c >= 32 && c <= 126);
}

int	min3(int top, int left, int diagonal)
{
	if (top <= left && top <= diagonal)
		return (top);
	if (left <= top && left <= diagonal)
		return (left);
	return (diagonal);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map->grid)
		return ;
	i = 0;
	while (i < map->rows)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

void	print_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		fprintf(stdout, "%s\n", map->grid[i]);
		i++;
	}
}

/* SOLVE BSQ ******************************************* */

void	free_dp(int **dp, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(dp[i]);
		i++;
	}
	free(dp);
}

void	solve_bsq(t_map *map)
{
	int	**dp;
	int	max;
	int	row_max;
	int	col_max;
	int	row_current;
	int	col_current;

	dp = calloc(map->rows, sizeof(int *));
	if (!dp)
		return ;

	row_current = 0;
	while (row_current < map->rows)
	{
		dp[row_current] = calloc(map->cols, sizeof(int));
		if (!dp[row_current])
		{
			free_dp(dp, row_current);
			return ;
		}
		row_current++;
	}

	max = 0;
	row_max = 0;
	col_max = 0;

	row_current = 0;
	while (row_current < map->rows)
	{
		col_current = 0;
		while (col_current < map->cols)
		{
			if (map->grid[row_current][col_current] == map->empty)
			{
				if (row_current == 0 || col_current == 0)
					dp[row_current][col_current] = 1;
				else
				{
					dp[row_current][col_current] = min3(
							dp[row_current - 1][col_current],
							dp[row_current][col_current - 1],
							dp[row_current - 1][col_current - 1]) + 1;
				}

				if (dp[row_current][col_current] > max)
				{
					max = dp[row_current][col_current];
					row_max = row_current;
					col_max = col_current;
				}
			}
			col_current++;
		}
		row_current++;
	}

	/* Replace biggest square with full character */
	if (max > 0)
	{
		row_current = row_max - max + 1;
		while (row_current <= row_max)
		{
			col_current = col_max - max + 1;
			while (col_current <= col_max)
			{
				map->grid[row_current][col_current] = map->full;
				col_current++;
			}
			row_current++;
		}
	}

	free_dp(dp, map->rows);
}

/* READ GRID ******************************************* */

int	read_grid(FILE *file_ptr, t_map *map)
{
	char	*line;
	char	*extra;
	size_t	capacity;
	ssize_t	len;
	int		i;
	int		j;

	map->grid = calloc(map->rows, sizeof(char *));
	if (!map->grid)
		return (0);

	i = 0;
	while (i < map->rows)
	{
		line = NULL;
		capacity = 0;

		len = getline(&line, &capacity, file_ptr);
		if (len == -1)
		{
			free(line);
			return (0);
		}

		/* Every row needs at least one cell + newline */
		if (len < 2 || line[len - 1] != '\n')
		{
			free(line);
			return (0);
		}

		/* Remove newline */
		line[len - 1] = '\0';
		len--;

		/* First row defines width */
		if (i == 0)
			map->cols = (int)len;
		else if ((int)len != map->cols)
		{
			free(line);
			return (0);
		}

		/* Validate map characters */
		j = 0;
		while (j < map->cols)
		{
			if (line[j] != map->empty
				&& line[j] != map->obstacle)
			{
				free(line);
				return (0);
			}
			j++;
		}

		map->grid[i] = line;
		i++;
	}

	/* There must not be extra rows */
	extra = NULL;
	capacity = 0;

	if (getline(&extra, &capacity, file_ptr) != -1)
	{
		free(extra);
		return (0);
	}
	free(extra);
	return (1);
}

/* READ HEADER ***************************************** */

int	read_header(FILE *file_ptr, t_map *map)
{
	char	newline;

	if (fscanf(file_ptr, "%d %c %c %c%c",
			&map->rows,
			&map->empty,
			&map->obstacle,
			&map->full,
			&newline) != 5)
		return (0);

	if (newline != '\n')
		return (0);

	if (map->rows <= 0)
		return (0);

	if (map->empty == map->obstacle
		|| map->empty == map->full
		|| map->obstacle == map->full)
		return (0);

	if (!is_printable(map->empty)
		|| !is_printable(map->obstacle)
		|| !is_printable(map->full))
		return (0);

	return (1);
}

/* READ MAP ******************************************** */

int	read_map(FILE *file_ptr, t_map *map)
{
	if (!read_header(file_ptr, map))
		return (0);
	if (!read_grid(file_ptr, map))
		return (0);
	return (1);
}

/* PROCESS MAP ***************************************** */

void	process_map(FILE *file_ptr)
{
	t_map	map;

	map = (t_map){0};

	if (!read_map(file_ptr, &map))
		fprintf(stderr, "map error\n");
	else
	{
		solve_bsq(&map);
		print_map(&map);
	}
	free_map(&map);
}

/* MAIN ************************************************ */

int	main(int argc, char **argv)
{
	FILE	*file_ptr;
	int		i;

	if (argc == 1)
	{
		process_map(stdin);
		return (0);
	}

	i = 1;
	while (i < argc)
	{
		file_ptr = fopen(argv[i], "r");

		if (!file_ptr)
			fprintf(stderr, "map error\n");
		else
		{
			process_map(file_ptr);
			fclose(file_ptr);
		}

		if (i < argc - 1)
			fprintf(stdout, "\n");

		i++;
	}
	return (0);
}
/*
    1. Read and validate the map.
        file/stdin
        ↓
        read header
        ↓
        read rows
        ↓
        validate everything
        ↓
        store in t_map
	
    2. Find the largest square made only of empty cells.

    3. Replace that square with the full character.
    
	4. Print the resulting map.
*/

/*
	main()
	│
	└── process_map()
			│
			├── read_map()
			│     ├── read_header()
			│     └── read_grid()
			│
			├── solve_bsq()
			│     ├── build DP table
			│     ├── find largest value
			│     └── replace square with full
			│
			├── print_map()
			│
			└── free_map()
*/