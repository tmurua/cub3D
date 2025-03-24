/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:39:43 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/24 16:16:09 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*	parses a header line and stores its corresponding value in t_game;
	checks start of line to delegate texture header or color header handling */
int	parse_header_line(char *line, t_game *game)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		return (handle_texture_header("Duplicate NO header", line,
				&game->hdr_no, &game->no_texture));
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (handle_texture_header("Duplicate SO header", line,
				&game->hdr_so, &game->so_texture));
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (handle_texture_header("Duplicate WE header", line,
				&game->hdr_we, &game->we_texture));
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (handle_texture_header("Duplicate EA header", line,
				&game->hdr_ea, &game->ea_texture));
	else if (ft_strncmp(line, "F", 1) == 0)
		return (handle_color_header("Duplicate Floor header", line,
				&game->hdr_f, &game->floor_color));
	else if (ft_strncmp(line, "C", 1) == 0)
		return (handle_color_header("Duplicate Ceiling header", line,
				&game->hdr_c, &game->ceiling_color));
	else
		return (print_err("Unknown header identifier"));
}
/* ft lines: 20 */

/*	expects line formats like "F 155,155,155" or "C 204,229,255";
	extracts substr after the identifier ("F " or "C "), splits it by commas;
	validates that there are exactly three numeric parts, and combines them
	into a single integer in 0xRRGGBB format */
int	parse_color_line(char *line, int *color_out)
{
	char	*data;
	char	**tokens;
	int		red;
	int		green;
	int		blue;

	data = ft_strtrim(line + 2, " ");
	if (!data)
		return (print_err("Color line: allocation failed"));
	tokens = ft_split(data, ',');
	free(data);
	if (!tokens)
		return (print_err("Color line: allocation failed"));
	if (validate_color_tokens(tokens, &red, &green, &blue) == -1)
		return (-1);
	*color_out = (red << 16) | (green << 8) | blue;
	ft_free_strs(tokens);
	return (1);
}

/*	checks that tokens contains exactly three numeric strings;
	converts each token to an integer and verifies they are between 0 and 255;
	on success, stores the values in red, green, and blue and returns 1;
	on error, frees tokens and returns -1 */
int	validate_color_tokens(char **tokens, int *red, int *green, int *blue)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	if (i != 3)
	{
		ft_free_strs(tokens);
		return (print_err("Color line: expected 3 components"));
	}
	*red = ft_atoi(tokens[0]);
	*green = ft_atoi(tokens[1]);
	*blue = ft_atoi(tokens[2]);
	if (*red < 0 || *red > 255 || *green < 0 || *green > 255 ||
		*blue < 0 || *blue > 255)
	{
		ft_free_strs(tokens);
		return (print_err("Color line: values must be between 0 and 255"));
	}
	return (1);
}
/* ft lines: 20 */

/*	expects a line like "NO textures/wolfenstein/grey_stone.xpm";
	skips the identifier, trims the remainder, and then checks that the file
	exists and its extension is ".xpm"; on success,
	stores a duplicate of the path in *texture_out */
int	parse_texture_line(char *line, char **texture_out)
{
	char	*data;
	char	*path;

	data = ft_strtrim(line + 3, " ");
	if (!data)
		return (print_err("Texture line: allocation failed"));
	path = ft_strdup(data);
	free(data);
	if (!path)
		return (print_err("Texture line: allocation failed"));
	if (access(path, F_OK) != 0)
	{
		free(path);
		return (print_err("Texture file does not exist"));
	}
	if (has_xpm_extension(path) == -1)
	{
		free(path);
		return (print_err("Texture file must have .xpm extension"));
	}
	*texture_out = path;
	return (1);
}
/* ft lines: 22 */

/* checks if the given filename ends with ".xpm" */
int	has_xpm_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (-1);
	if (ft_strncmp(filename + len - 4, ".xpm", 4) == 0)
		return (1);
	return (-1);
}
/* ft lines: 8 */
