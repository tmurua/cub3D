/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:21:06 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/13 21:27:03 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#include "../../include/cubthreed.h"

/*	copies dimensions from parsed map and converts the array of strings
	into an integer array stored in d->map */
void	load_parsed_map(t_data *d, t_game *game)
{
	d->map_rows = game->map.rows;
	d->map_cols = game->map.cols;
	d->map = convert_parsed_map(game);
	if (!d->map)
	{
		perror("Error converting parsed map");
		exit(EXIT_FAILURE);
	}
}

/*	converts game->map.lines into an integer array
	'1' becomes 1 (wall) and any other valid character becomes 0 (open space)
	returns pointer to new integer array or NULL on allocation failure */
int	*convert_parsed_map(t_game *game)
{
	int	*new_map;
	int	row;
	int	col;
	int	index;

	new_map = malloc(game->map.rows * game->map.cols * sizeof(int));
	if (!new_map)
	{
		perror("Failed to allocate memory for converted map");
		return (NULL);
	}
	row = 0;
	while (row < game->map.rows)
	{
		col = 0;
		while (col < game->map.cols)
		{
			index = row * game->map.cols + col;
			new_map[index] = convert_map_cell(game->map.lines[row][col]);
			col++;
		}
		row++;
	}
	return (new_map);
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
