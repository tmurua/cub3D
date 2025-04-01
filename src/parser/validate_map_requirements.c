/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_requirements.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:48:39 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/01 20:15:10 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*	validate only allowed chars; checks only one player exists; checks that map
	is completely enclosed by walls using a flood fill algorithm */
int	validate_map_requirements(t_game *game)
{
	if (validate_allowed_chars(game) == -1)
		return (-1);
	if (validate_player_position(game) == -1)
		return (-1);
	if (perform_flood_fill(game) == -1)
		return (-1);
	return (1);
}

/* iterates over every row in game->map and checks if every char is allowed */
int	validate_allowed_chars(t_game *game)
{
	int		i;
	int		j;
	char	*row;

	i = 0;
	while (i < game->map.rows)
	{
		row = game->map.lines[i];
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

/* returns 1 if the character c is in the allowed set, 0 otherwise */
int	is_allowed_map_char(char c)
{
	int		j;
	char	*allowed;

	allowed = ALLOWED_MAP_CHARS;
	j = 0;
	while (allowed[j])
	{
		if (c == allowed[j])
			return (1);
		j++;
	}
	return (0);
}

/*	scans game->map.lines for start pos indicated by 'N', 'S', 'E', or 'W';
	ensures exactly one starting position exists; stores the player's centered
	coords and orientation in game, and replaces the starting cell with '0' */
int	validate_player_position(t_game *game)
{
	int	i;
	int	j;
	int	found;

	found = 0;
	i = 0;
	while (i < game->map.rows)
	{
		j = 0;
		while (game->map.lines[i][j])
		{
			if (process_player_in_cell(game, i, j, &found) == -1)
				return (-1);
			j++;
		}
		i++;
	}
	if (!found)
		return (print_err("No player position found"));
	return (1);
}

/*	checks the cell at (row, col) in game->map.map;
	if player's start pos is found, verifies that no previous one was found;
	stores coords and orientation in game, and replaces cell with '0';
	uses pointer 'found' to track if a starting pos has already been processed;
	returns 1 on success or -1 if a duplicate player is found */
int	process_player_in_cell(t_game *game, int row, int col, int *found)
{
	if (game->map.lines[row][col] == 'N' || game->map.lines[row][col] == 'S'
		|| game->map.lines[row][col] == 'E'
		|| game->map.lines[row][col] == 'W')
	{
		if (*found)
			return (print_err("Multiple player positions found"));
		*found = 1;
		game->player.x = col + 0.5;
		game->player.y = row + 0.5;
		game->player.orientation = game->map.lines[row][col];
		game->map.lines[row][col] = '0';
	}
	return (1);
}
