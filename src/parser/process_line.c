/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:50:53 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/15 12:30:50 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/* delegates line processing to header or map processing depending on its type*/
int	check_line_type(char *input_line, t_game *game)
{
	if (input_line[0] == '\0')
		return (1);
	if (is_header_line(input_line))
	{
		if (game->map.map_started)
			return (print_err("Header found after map content"));
		if (parse_header_line(input_line, game) == -1)
			return (-1);
	}
	else
	{
		game->map.map_started = 1;
		if (process_map_line(input_line, game) == -1)
			return (-1);
	}
	return (1);
}

/*	returns 1 if line begins with valid header identifier, else 0 */
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

/* parses a header line and delegates processing to texture or color handlers */
int	parse_header_line(char *line, t_game *game)
{
	if (ft_strncmp(line, "EA", 2) == 0)
		return (handle_texture_hdr(line, &game->texture.no, &game->header.no));
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (handle_texture_hdr(line, &game->texture.so, &game->header.so));
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (handle_texture_hdr(line, &game->texture.we, &game->header.we));
	else if (ft_strncmp(line, "NO", 2) == 0)
		return (handle_texture_hdr(line, &game->texture.ea, &game->header.ea));
	else if (ft_strncmp(line, "C", 1) == 0)
		return (handle_color_hdr(line, &game->color.floor, &game->header.f));
	else if (ft_strncmp(line, "F", 1) == 0)
		return (handle_color_hdr(line, &game->color.ceiling, &game->header.c));
	else
		return (print_err("Unknown header identifier"));
}

/*	appends map line to current array element in game->map.lines, updating row
	count and reallocating the map array of strings to include the new line */
int	process_map_line(char *line, t_game *game)
{
	char	**map_lines;
	int		i;

	map_lines = ft_calloc(game->map.rows + 2, sizeof(char *));
	if (!map_lines)
		return (print_err("Memory allocation failed"));
	i = 0;
	while (i < game->map.rows)
	{
		map_lines[i] = game->map.lines[i];
		i++;
	}
	map_lines[i] = ft_strdup(line);
	if (!map_lines[i])
	{
		free(map_lines);
		return (print_err("Memory allocation failed"));
	}
	map_lines[i + 1] = NULL;
	free(game->map.lines);
	game->map.lines = map_lines;
	game->map.rows++;
	return (1);
}
