/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:16:37 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/26 16:38:42 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/* validates map layout stored in game->map; checks allowed chars and borders */
int	validate_map_layout(t_game *game)
{
	if (validate_all_borders(game) == -1)
		return (-1);
	if (validate_allowed_chars(game) == -1)
		return (-1);
	return (1);
}
/* ft lines: 5 */

/*	checks that top and bottom rows (after trimming) have proper borders,
	and that every row (trimmed) starts and ends with a wall ('1') */
int	validate_all_borders(t_game *game)
{
	int	i;

	if (validate_row_borders(game->mapdata.map[0]) == -1
		|| validate_row_borders(game->mapdata.map[game->mapdata.rows - 1])
		== -1)
		return (print_err("Map layout: top and bottom borders must be walls"));
	i = 0;
	while (i < game->mapdata.rows)
	{
		if (validate_row_borders(game->mapdata.map[i]) == -1)
			return (print_err("Map layout: side borders must be walls"));
		i++;
	}
	return (1);
}
/* ft lines: 14 */

/*	trims leading and trailing spaces from a map row and checks that first and
	last characters of the trimmed row are '1'. Returns 1 if valid, else -1 */
int	validate_row_borders(char *row)
{
	char	*trimmed;
	int		len;

	trimmed = ft_strtrim(row, " ");
	if (!trimmed)
		return (-1);
	len = ft_strlen(trimmed);
	if (len == 0 || trimmed[0] != '1' || trimmed[len - 1] != '1')
	{
		free(trimmed);
		return (-1);
	}
	free(trimmed);
	return (1);
}
/* ft lines: 14 */

/* iterates over every row in game->map and checks if every char is allowed */
int	validate_allowed_chars(t_game *game)
{
	int		i;
	int		j;
	char	*row;

	i = 0;
	while (i < game->mapdata.rows)
	{
		row = game->mapdata.map[i];
		j = 0;
		while (row[j])
		{
			if (!is_allowed_map_char(row[j]))
				return (print_err("Map layout: invalid character found"));
			j++;
		}
		i++;
	}
	return (1);
}
/* ft lines: 18 */

/* returns 1 if the character c is in the allowed set, 0 otherwise */
int	is_allowed_map_char(char c)
{
	int		j;
	char	*allowed;

	allowed = " 01NSEW";
	j = 0;
	while (allowed[j])
	{
		if (c == allowed[j])
			return (1);
		j++;
	}
	return (0);
}
/* ft lines: 12 */
