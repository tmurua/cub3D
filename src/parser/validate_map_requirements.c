/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_requirements.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:48:39 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/15 17:17:45 by tmurua           ###   ########.fr       */
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

/* iterates over each map line in game->map.lines and validates every char */
int	validate_allowed_chars(t_game *game)
{
	int		current_row_pos;
	int		current_char_pos;
	char	*map_line;

	current_row_pos = 0;
	while (current_row_pos < game->map.rows)
	{
		map_line = game->map.lines[current_row_pos];
		current_char_pos = 0;
		while (map_line[current_char_pos])
		{
			if (!is_allowed_map_char(map_line[current_char_pos]))
				return (print_err("Map layout: invalid character found"));
			current_char_pos++;
		}
		current_row_pos++;
	}
	return (1);
}

/* returns 1 if current_char is in the allowed_chars set, 0 otherwise */
int	is_allowed_map_char(char current_char)
{
	int		i;
	char	*allowed_chars;

	allowed_chars = ALLOWED_MAP_CHARS;
	i = 0;
	while (allowed_chars[i])
	{
		if (current_char == allowed_chars[i])
			return (1);
		i++;
	}
	return (0);
}

/*	loops all elements(y) of all strings(x)(map lines) in game->map.lines;
	uses a flag(found) to determine if exactly one player exists; */
int	validate_player_position(t_game *game)
{
	int	x;
	int	y;
	int	found;

	found = 0;
	x = 0;
	while (x < game->map.rows)
	{
		y = 0;
		while (game->map.lines[x][y])
		{
			if (process_player_in_cell(game, x, y, &found) == -1)
				return (-1);
			y++;
		}
		x++;
	}
	if (!found)
		return (print_err("No player position found"));
	return (1);
}

/*	checks current cell at game->map.lines[x][y];
	if player(N, S, E, W) is found, verifies that no previous one was found;
	stores coords(x,y) and orientation in game->player, and replaces cell with 0;
	uses pointer 'found' to track if a starting pos has already been processed;
	returns -1 if a duplicate player is found, otherwise always returns 1 */
int	process_player_in_cell(t_game *game, int x, int y, int *found)
{
	if (game->map.lines[x][y] == 'N' || game->map.lines[x][y] == 'S'
		|| game->map.lines[x][y] == 'E'
		|| game->map.lines[x][y] == 'W')
	{
		if (*found)
			return (print_err("Multiple player positions found"));
		*found = 1;
		game->player.x = x + 0.5;
		game->player.y = y + 0.5;
		game->player.orientation = game->map.lines[x][y];
		game->map.lines[x][y] = '0';
	}
	return (1);
}
