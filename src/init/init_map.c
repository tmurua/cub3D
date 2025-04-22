/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:21:06 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/22 14:02:17 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#include "../../include/cubthreed.h"

/*	copies dimensions from parsed map and converts the array of strings
	into an integer array stored in d->map */
void	load_parsed_map(t_data *d, t_game *game)
{
	d->map_rows = game->map.rows;
	d->map = convert_parsed_map(game, &d->map_cols);
	if (!d->map)
	{
		perror("Error converting parsed map");
		exit(EXIT_FAILURE);
	}
}

/*	build a padded **char map, alloc a new int map, fill it, clean, return it
	fill it, clean up, and return it (or NULL on error) */
int	*convert_parsed_map(t_game *game, int *map_cols)
{
	char	**padded_map_lines;
	int		*integer_map;
	int		map_rows;

	map_rows = game->map.rows;
	padded_map_lines = copy_padded_map_lines(game, map_cols);
	if (!padded_map_lines)
		return (NULL);
	integer_map = malloc(map_rows * *map_cols * sizeof(int));
	if (!integer_map)
	{
		perror("Failed to allocate converted map");
		free_map_lines_copy(padded_map_lines, map_rows);
		return (NULL);
	}
	fill_converted_map(integer_map, padded_map_lines, map_rows, *map_cols);
	free_map_lines_copy(padded_map_lines, map_rows);
	return (integer_map);
}

/* walk the padded char‐map and write into the int‐map */
void	fill_converted_map(int *map, char **lines, int rows, int cols)
{
	int	current_row;
	int	current_col;
	int	index;

	current_row = 0;
	while (current_row < rows)
	{
		current_col = 0;
		while (current_col < cols)
		{
			index = current_row * cols + current_col;
			map[index] = convert_map_cell(lines[current_row][current_col]);
			current_col++;
		}
		current_row++;
	}
}

/*	converts a single char from parsed map into an integer.
	'1' becomes 1 (wall) and any other valid character becomes 0 (open space) */
int	convert_map_cell(char c)
{
	if (c == '1')
		return (1);
	return (0);
}

/*	computes the 1D array index given 2D coordinates (x, y) using number of cols
	stored in d->map_cols; returns the computed index */
int	get_map_index(t_data *d, int x, int y)
{
	return (x * d->map_cols + y);
}
