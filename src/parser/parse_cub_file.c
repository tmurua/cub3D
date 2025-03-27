/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:55:47 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/27 15:39:28 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*	opens .cub file, checks if it's empty, processes every line, and validates
	basic map layout & advanced validations (player pos and flood fill enclos)*/
int	parse_cub_file(t_game *game, char *filename)
{
	int	fd;
	int	found_non_empty;
	int	result;

	found_non_empty = 0;
	fd = open_cub_file(filename);
	if (fd < 0)
		return (-1);
	result = process_file_lines(fd, game, &found_non_empty);
	close(fd);
	if (result == -1)
		return (-1);
	if (!found_non_empty)
		return (print_err("File is empty"));
	if (!game->header.hdr_no || !game->header.hdr_so
		|| !game->header.hdr_we || !game->header.hdr_ea
		|| !game->header.hdr_f || !game->header.hdr_c)
		return (print_err("Missing required header(s)"));
	if (validate_map_layout(game) == -1)
		return (-1);
	if (validate_map_requirements(game) == -1)
		return (-1);
	return (1);
}

/*	processes each line from file via process_single_file_line(),
	updates found_non_empty, and frees the leftover when done */
int	process_file_lines(int fd, t_game *game, int *found_non_empty)
{
	char	*input_line;
	char	*leftover;
	int		result;

	leftover = NULL;
	input_line = get_next_line(fd, &leftover);
	while (input_line != NULL)
	{
		result = process_single_file_line(input_line, game, found_non_empty);
		if (result == -1)
		{
			free(leftover);
			return (-1);
		}
		input_line = get_next_line(fd, &leftover);
	}
	free(leftover);
	return (1);
}

/*	trims a line, updates found_non_empty flag if line is non‑empty, calls
	process_line() on trimmed line, frees its memory, and returns result */
int	process_single_file_line(char *line, t_game *game, int *found_non_empty)
{
	char	*trim_line;
	int		res;

	trim_line = ft_strtrim(line, " \n\r\t");
	free(line);
	if (trim_line)
	{
		if (trim_line[0] != '\0')
			*found_non_empty = 1;
		res = process_line(trim_line, game);
		free(trim_line);
		return (res);
	}
	return (1);
}

/* validates that the file has a ".cub" extension and then opens it */
int	open_cub_file(char *filename)
{
	int	fd;

	if (has_cub_extension(filename) == -1)
		return (print_err("File must have a .cub extension"));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_err("Error opening *.cub file"));
	return (fd);
}

/* compare last 4 chars of filename with ".cub" */
int	has_cub_extension(char *filename)
{
	size_t	filename_length;

	filename_length = ft_strlen(filename);
	if (filename_length < 4)
		return (-1);
	if (ft_strncmp(filename + filename_length - 4, ".cub", 4) == 0)
		return (1);
	else
		return (-1);
}
