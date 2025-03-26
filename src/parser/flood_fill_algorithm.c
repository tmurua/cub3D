/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_algorithm.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:03:51 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/26 17:35:14 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*	creates rectangular copy of map using copy_map_padded(), then uses
	flood_fill_on_copy() to verify that the map is enclosed by walls;
	returns 1 if the flood fill remains enclosed, -1 if it escapes */
int	perform_flood_fill(t_game *game)
{
	int			cols;
	char		**map_copy;
	int			result;
	t_mapdata	start;

	map_copy = copy_map_padded(game, &cols);
	if (!map_copy)
		return (print_err("Map copy failed: unable to pad map"));
	start.rows = (int)(game->player.y);
	start.cols = (int)(game->player.x);
	result = flood_fill_on_copy(map_copy, game->mapdata.rows, cols, &start);
	free_map_copy(map_copy, game->mapdata.rows);
	if (result == -1)
		return (print_err("Map is not enclosed by walls"));
	return (1);
}

/*	wraps a padded map copy into a temporary t_game structure and calls
	flood_fill() starting from (start_rows, start_cols) */
int	flood_fill_on_copy(char **map_copy, int rows, int cols, t_mapdata *start)
{
	t_game	temp;

	temp.mapdata.map = map_copy;
	temp.mapdata.rows = rows;
	temp.mapdata.cols = cols;
	return (flood_fill(&temp, start->rows, start->cols));
}

/*	recursively fills empty space starting from (r, c) in map;
	if it goes out-of-bound or reaches a cell that is not '0', a wall or visited,
	returns -1 to indicate that the flood has escaped;
	marks visited cells as 'V'; returns 0 on success */
int	flood_fill(t_game *game, int r, int c)
{
	if (r < 0 || c < 0 || r >= game->mapdata.rows || c >= game->mapdata.cols)
		return (-1);
	if (game->mapdata.map[r][c] == '1' || game->mapdata.map[r][c] == 'V')
		return (0);
	if (game->mapdata.map[r][c] == ' ')
		return (-1);
	game->mapdata.map[r][c] = 'V';
	if (flood_fill(game, r - 1, c) == -1)
		return (-1);
	if (flood_fill(game, r + 1, c) == -1)
		return (-1);
	if (flood_fill(game, r, c - 1) == -1)
		return (-1);
	if (flood_fill(game, r, c + 1) == -1)
		return (-1);
	return (0);
}
