/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_padding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:08:12 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/26 17:39:04 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*	creates a rectangular copy of game->map by first computing the maximum
	trimmed row length, then creating a padded copy of each row with pad_row()
	with wall characters ('1') if necessary;
	returns the new array and sets *cols to the maximum length */
char	**copy_map_padded(t_game *game, int *cols)
{
	int		max_len;
	char	**copy;
	int		i;

	max_len = get_max_trimmed_length(game);
	if (max_len < 0)
		return (NULL);
	*cols = max_len;
	copy = ft_calloc(game->mapdata.rows + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < game->mapdata.rows)
	{
		copy[i] = pad_row(game->mapdata.map[i], max_len);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}

/*	iterates over game->map and returns max length among all rows
	after trimming leading and trailing spaces */
int	get_max_trimmed_length(t_game *game)
{
	int		i;
	int		max;
	char	*trim;
	int		len;

	max = 0;
	i = 0;
	while (i < game->mapdata.rows)
	{
		trim = ft_strtrim(game->mapdata.map[i], " ");
		if (!trim)
			return (-1);
		len = ft_strlen(trim);
		if (len > max)
			max = len;
		free(trim);
		i++;
	}
	return (max);
}

/*	creates a new string for a single row by trimming it and then padding it
	with wall characters ('1') to reach the specified max_len;
	returns the new padded row, or NULL on allocation failure */
char	*pad_row(char *row, int max_len)
{
	char	*trim;
	char	*padded;

	trim = ft_strtrim(row, " ");
	if (!trim)
		return (NULL);
	padded = ft_calloc(max_len + 1, sizeof(char));
	if (!padded)
	{
		free(trim);
		return (NULL);
	}
	fill_padded_row(padded, trim, max_len);
	free(trim);
	return (padded);
}

/*	fills the 'padded' string with the contents of 'trim' up to its length,
	and pads the rest with wall characters ('1') until reaching max_len */
void	fill_padded_row(char *padded, char *trim, int max_len)
{
	int	len;
	int	j;

	len = ft_strlen(trim);
	j = 0;
	while (j < max_len)
	{
		if (j < len)
			padded[j] = trim[j];
		else
			padded[j] = '1';
		j++;
	}
}

/* frees a rectangular map copy created by copy_map() */
void	free_map_copy(char **map_copy, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}
