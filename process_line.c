/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:50:53 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/22 15:42:46 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* trims single line from .cub file and delegates to header or map processing */
int	process_line(char *input_line, t_game *game)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(input_line, " \n\r\t");
	if (!trimmed_line)
		return (print_err("Memory allocation failed"));
	if (trimmed_line[0] == '\0')
		return (free_and_return(trimmed_line, 1));
	if (is_header_line(trimmed_line))
	{
		if (process_header_line(trimmed_line, game) == -1)
			return (free_and_return(trimmed_line, -1));
	}
	else if (process_map_line(trimmed_line, game) == -1)
		return (free_and_return(trimmed_line, -1));
	free(trimmed_line);
	return (1);
}
/* ft lines: 16 */

/*	returns 1 if trimmed line begins with valid header identifier, else 0 */
int	is_header_line(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (1);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}
/* ft lines: 13 */

/* parses a header line and stores the corresponding value in t_game.
**  Expected formats:
**   "NO <path>", "SO <path>", "WE <path>", "EA <path>"
**   "F <color>", "C <color>" */
int	process_header_line(char *line, t_game *game)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1])
		return (print_err("Invalid header format"));
	if (ft_strncmp(tokens[0], "NO", 2) == 0)
		game->no_texture = ft_strdup(tokens[1]);
	else if (ft_strncmp(tokens[0], "SO", 2) == 0)
		game->so_texture = ft_strdup(tokens[1]);
	else if (ft_strncmp(tokens[0], "WE", 2) == 0)
		game->we_texture = ft_strdup(tokens[1]);
	else if (ft_strncmp(tokens[0], "EA", 2) == 0)
		game->ea_texture = ft_strdup(tokens[1]);
	else if (ft_strncmp(tokens[0], "F", 1) == 0)
		game->floor_color = ft_atoi(tokens[1]);
	else if (ft_strncmp(tokens[0], "C", 1) == 0)
		game->ceiling_color = ft_atoi(tokens[1]);
	else
	{
		ft_free_strs(tokens);
		return (print_err("Unknown header identifier"));
	}
	ft_free_strs(tokens);
	return (1);
}
/* ft lines: 24 */

/*	appends a map line to the game->map array;
	game->map field is assumed to be a NULL-terminated array of strings */
int	process_map_line(char *line, t_game *game)
{
	char	**new_map;
	int		i;

	new_map = ft_calloc(game->map_rows + 2, sizeof(char *));
	if (!new_map)
		return (print_err("Memory allocation failed"));
	i = 0;
	while (i < game->map_rows)
	{
		new_map[i] = game->map[i];
		i++;
	}
	new_map[i] = ft_strdup(line);
	if (!new_map[i])
	{
		free(new_map);
		return (print_err("Memory allocation failed"));
	}
	new_map[i + 1] = NULL;
	free(game->map);
	game->map = new_map;
	game->map_rows++;
	return (1);
}
/* ft lines: 23 */

void	ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
/* ft lines: 8 */
