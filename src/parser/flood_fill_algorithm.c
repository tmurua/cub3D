/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_algorithm.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:03:51 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/02 16:24:26 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*	creates rectangular copy of game->map.lines using copy_padded_map_lines(),
	then uses flood_fill_on_copy() to verify that the map is enclosed by walls;
	returns 1 if the flood fill remains enclosed, -1 if it escapes */
int	perform_flood_fill(t_game *game)
{
	int		total_cols;
	char	**map_lines_copy;
	int		result;
	t_map	start;

	map_lines_copy = copy_padded_map_lines(game, &total_cols);
	if (!map_lines_copy)
		return (print_err("Map copy failed: unable to pad map"));
	start.rows = (int)(game->player.x);
	start.cols = (int)(game->player.y);
	result = flood_fill_on_copy(map_lines_copy, game->map.rows, total_cols,
			&start);
	free_map_lines_copy(map_lines_copy, game->map.rows);
	if (result == -1)
		return (print_err("Map is not enclosed by walls"));
	return (1);
}

/*	wraps a padded map_lines copy into a temporary t_game structure and calls
	flood_fill() starting from (start_rows, start_cols) */
int	flood_fill_on_copy(char **map_lines_copy, int rows, int cols, t_map *start)
{
	t_game	temp;

	temp.map.lines = map_lines_copy;
	temp.map.rows = rows;
	temp.map.cols = cols;
	return (flood_fill(&temp, start->rows, start->cols));
}

/*	checks if x & y are in limits of map.rows and map.cols, and if cell is ' '
	if cell is wall('1') or visited('V'), there's nothing to fill, returns 0;
	fill cell with 'V', indicating it was visited, then recursively calls
	itself for the four adjacent cells (up, down, left, right) */
int	flood_fill(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map.rows || y < 0 || y >= game->map.cols)
		return (-1);
	if (game->map.lines[x][y] == ' ')
		return (-1);
	if (game->map.lines[x][y] == '1' || game->map.lines[x][y] == 'V')
		return (0);
	game->map.lines[x][y] = 'V';
	if (flood_fill(game, x - 1, y) == -1)
		return (-1);
	if (flood_fill(game, x + 1, y) == -1)
		return (-1);
	if (flood_fill(game, x, y - 1) == -1)
		return (-1);
	if (flood_fill(game, x, y + 1) == -1)
		return (-1);
	return (0);
}
