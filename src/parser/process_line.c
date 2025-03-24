/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:50:53 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/24 16:42:47 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

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
		if (parse_header_line(trimmed_line, game) == -1)
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
/* ft lines: 9 */
