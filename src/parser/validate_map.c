/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:48:39 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/26 16:28:57 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*	validates advanced map requirements:
	- ensures exactly one player position is defined
	- checks that the map is completely enclosed by walls (via flood fill) */
int	validate_map_advanced(t_game *game)
{
	if (validate_player_position(game) == -1)
		return (-1);
	if (perform_flood_fill(game) == -1)
		return (-1);
	return (1);
}
/* ft lines: 5 */

/*	scans game->mapdata.map for start pos indicated by 'N', 'S', 'E', or 'W';
	ensures exactly one starting position exists; stores the player's centered
	coords and orientation in game, and replaces the starting cell with '0' */
int	validate_player_position(t_game *game)
{
	int	i;
	int	j;
	int	found;

	found = 0;
	i = 0;
	while (i < game->mapdata.rows)
	{
		j = 0;
		while (game->mapdata.map[i][j])
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
/* ft lines: 20 */

/*	checks the cell at (row, col) in game->map;
	if player's start pos is found, verifies that no previous one was found;
	stores centered coords and orientation in game, and replaces cell with '0';
	uses pointer 'found' to track if a starting pos has already been processed;
	returns 1 on success or -1 if a duplicate player is found */
int	process_player_in_cell(t_game *game, int row, int col, int *found)
{
	if (game->mapdata.map[row][col] == 'N' || game->mapdata.map[row][col] == 'S'
		|| game->mapdata.map[row][col] == 'E'
		|| game->mapdata.map[row][col] == 'W')
	{
		if (*found)
			return (print_err("Multiple player positions found"));
		*found = 1;
		game->player.x = col + 0.5;
		game->player.y = row + 0.5;
		game->player.orientation = game->mapdata.map[row][col];
		game->mapdata.map[row][col] = '0';
	}
	return (1);
}
/* ft lines: 13 */
