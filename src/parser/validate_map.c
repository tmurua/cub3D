/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:48:39 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/26 13:50:46 by tmurua           ###   ########.fr       */
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
/* ft lines:  5 */

/*	scans game->map for a starting position indicated by 'N', 'S', 'E', or 'W';
	ensures exactly one starting position exists; stores the player's centered
	coords and orientation in game, and replaces the starting cell with '0' */
int	validate_player_position(t_game *game)
{
	int	i;
	int	j;
	int	found;

	found = 0;
	i = 0;
	while (i < game->map_rows)
	{
		j = 0;
		while (game->map[i][j])
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
	if (game->map[row][col] == 'N' || game->map[row][col] == 'S' ||
		game->map[row][col] == 'E' || game->map[row][col] == 'W')
	{
		if (*found)
			return (print_err("Multiple player positions found"));
		*found = 1;
		game->player_x = col + 0.5;
		game->player_y = row + 0.5;
		game->player_orientation = game->map[row][col];
		game->map[row][col] = '0';
	}
	return (1);
}
/* ft lines: 12 */

/*	creates rectangular copy of map, and flood fill starting from player's pos
	returns 1 if the flood fill remains enclosed, -1 if it escapes */
int	perform_flood_fill(t_game *game)
{
	int		cols;
	char	**map_copy;
	int		result;
	int		player_row;
	int		player_col;

	map_copy = copy_map_padded(game, &cols);
	if (!map_copy)
		return (print_err("Map copy failed: unable to pad map"));
	player_col = (int)(game->player_x);
	player_row = (int)(game->player_y);
	result = flood_fill(map_copy, game->map_rows, cols, player_row, player_col);
	free_map_copy(map_copy, game->map_rows);
	if (result == -1)
		return (print_err("Map is not enclosed by walls"));
	return (1);
}
/* ft lines:  16 */

/*	recursively fills empty space starting from (r, c) in map;
	if it goes out-of-bound or reaches a cell that is not '0', a wall or visited,
	returns -1 to indicate that the flood has escaped;
	marks visited cells as 'V'; returns 0 on success. */
int	flood_fill(char **map, int rows, int cols, int r, int c)
{
	if (r < 0 || c < 0 || r >= rows || c >= cols)
		return (-1);
	if (map[r][c] == '1' || map[r][c] == 'V')
		return (0);
	if (map[r][c] == ' ')
		return (-1);
	map[r][c] = 'V';
	if (flood_fill(map, rows, cols, r - 1, c) == -1)
		return (-1);
	if (flood_fill(map, rows, cols, r + 1, c) == -1)
		return (-1);
	if (flood_fill(map, rows, cols, r, c - 1) == -1)
		return (-1);
	if (flood_fill(map, rows, cols, r, c + 1) == -1)
		return (-1);
	return (0);
}
/* ft lines: 16 */

/*	creates a rectangular copy of game->map by first computing the maximum
	trimmed row length, then creating a padded copy of each row with pad_row()
	with wall characters ('1') if necessary;
	returns the new array and sets *cols to the maximum length;
	returns NULL on allocation failure. */
char	**copy_map_padded(t_game *game, int *cols)
{
	int		max_len;
	char	**copy;
	int		i;

	max_len = get_max_trimmed_length(game);
	if (max_len < 0)
		return (NULL);
	*cols = max_len;
	copy = ft_calloc(game->map_rows + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < game->map_rows)
	{
		copy[i] = pad_row(game->map[i], max_len);
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
/* ft lines: 25 */

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
	while (i < game->map_rows)
	{
		trim = ft_strtrim(game->map[i], " ");
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
/* ft lines:  19 */

/*	creates a new string for a single row by trimming it and then padding it
	with wall characters ('1') to reach the specified max_len;
	returns the new padded row, or NULL on allocation failure */
char	*pad_row(char *row, int max_len)
{
	char	*trim;
	char	*padded;
	int		len;
	int		j;

	trim = ft_strtrim(row, " ");
	if (!trim)
		return (NULL);
	len = ft_strlen(trim);
	padded = ft_calloc(max_len + 1, sizeof(char));
	if (!padded)
	{
		free(trim);
		return (NULL);
	}
	j = 0;
	while (j < max_len)
	{
		if (j < len)
			padded[j] = trim[j];
		else
			padded[j] = '1';
		j++;
	}
	free(trim);
	return (padded);
}
/* ft lines:  26 */

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
/* ft lines:  9 */
