/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:33:15 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/01 18:49:08 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*	checks if a texture header is duplicated, then parses the texture line,
	sets the header flag to indicate current texture header was parsed */
int	handle_texture_hdr(char *line, char **texture_field, int *header_flag)
{
	if (*header_flag)
		return (print_err("Found duplicated header"));
	if (parse_texture_line(line, texture_field) == -1)
		return (-1);
	*header_flag = 1;
	return (1);
}

/*	expects a line like "NO textures/wolfenstein/grey_stone.xpm"; skips
	identifier, trims remainder, and checks if file exists and if its extension
	is .xpm; stores dup of file path in appropriate field of texture struct */
int	parse_texture_line(char *line, char **texture_field)
{
	char	*texture_file_path;

	texture_file_path = ft_strtrim(line + 3, " ");
	if (!texture_file_path)
		return (print_err("Texture header: allocation failed"));
	if (check_if_file_exists(texture_file_path) == -1)
	{
		free(texture_file_path);
		return (print_err("Texture file does not exist"));
	}
	if (has_xpm_extension(texture_file_path) == -1)
	{
		free(texture_file_path);
		return (print_err("Texture file must have .xpm extension"));
	}
	*texture_field = texture_file_path;
	return (1);
}

/* checks if the file at texture_file_path can be opened for reading */
int	check_if_file_exists(char *texture_file_path)
{
	int	fd;

	fd = open(texture_file_path, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	return (1);
}

/* checks if the given texture_file_path ends with ".xpm" */
int	has_xpm_extension(char *texture_file_path)
{
	size_t	len;

	len = ft_strlen(texture_file_path);
	if (len < 4)
		return (-1);
	if (ft_strncmp(texture_file_path + len - 4, ".xpm", 4) == 0)
		return (1);
	return (-1);
}
