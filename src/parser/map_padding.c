/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_padding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:08:12 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/22 14:39:29 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*	creates a rectangular copy of game->map.lines by 1st getting max row length,
	then creating a padded copy of each row with pad_row() with chars '^';
	returns the new array and sets *total_cols to the max_row_length */
char	**copy_padded_map_lines(t_game *game, int *total_cols)
{
	int		max_row_length;
	char	**map_lines_copy;
	int		i;

	max_row_length = get_max_row_length(game);
	if (max_row_length < 0)
		return (NULL);
	*total_cols = max_row_length;
	map_lines_copy = ft_calloc(game->map.rows + 1, sizeof(char *));
	if (!map_lines_copy)
		return (NULL);
	i = 0;
	while (i < game->map.rows)
	{
		map_lines_copy[i] = pad_row(game->map.lines[i], max_row_length);
		if (!map_lines_copy[i])
		{
			free_map_lines_copy(map_lines_copy, i);
			return (NULL);
		}
		i++;
	}
	return (map_lines_copy);
}

/*	iterates over game->map.lines and returns max length among all rows */
int	get_max_row_length(t_game *game)
{
	int		i;
	int		max_row_length;
	char	*current_row;
	int		current_row_length;

	max_row_length = 0;
	i = 0;
	while (i < game->map.rows)
	{
		current_row = game->map.lines[i];
		if (!current_row)
			return (-1);
		current_row_length = ft_strlen(current_row);
		if (current_row_length > max_row_length)
			max_row_length = current_row_length;
		i++;
	}
	return (max_row_length);
}

/*	creates new row for each map line by adding '^' to match max_row_length */
char	*pad_row(char *current_row, int max_row_length)
{
	char	*padded_row;

	padded_row = ft_calloc(max_row_length + 1, sizeof(char));
	if (!padded_row)
		return (NULL);
	fill_padded_row(padded_row, current_row, max_row_length);
	return (padded_row);
}

/*	fills padded_row with the contents of trimmed_row up to its length,
	and pads the rest with wall chars ('^') until reaching max_row_length */
void	fill_padded_row(char *padded_row, char *current_row, int max_row_length)
{
	int	current_row_length;
	int	current_char_pos;

	current_row_length = ft_strlen(current_row);
	current_char_pos = 0;
	while (current_char_pos < max_row_length)
	{
		if (current_char_pos < current_row_length)
			padded_row[current_char_pos] = current_row[current_char_pos];
		else
			padded_row[current_char_pos] = '^';
		current_char_pos++;
	}
}

/* frees the rectangular map_lines_copy created by copy_padded_map_lines() */
void	free_map_lines_copy(char **map_lines_copy, int map_rows)
{
	int	i;

	i = 0;
	while (i < map_rows)
	{
		free(map_lines_copy[i]);
		i++;
	}
	free(map_lines_copy);
}
