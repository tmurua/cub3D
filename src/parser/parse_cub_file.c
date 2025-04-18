/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:55:47 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/16 19:54:45 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*	opens .cub file, processes every line, checks if it's empty, if all headers
	exist and all map requirements, valid chars, nbr of players and enclosure */
int	parse_cub_file(t_game *game, char *filename)
{
	int	fd;
	int	found_non_empty;
	int	line_processing_status;

	found_non_empty = 0;
	fd = open_cub_file(filename);
	if (fd < 0)
		return (-1);
	line_processing_status = handle_lines_loop(fd, game, &found_non_empty);
	close(fd);
	if (line_processing_status == -1)
		return (-1);
	if (!found_non_empty)
		return (print_err("File is empty"));
	if (!game->header.no || !game->header.so || !game->header.we
		|| !game->header.ea || !game->header.f || !game->header.c)
		return (print_err("Missing required header(s)"));
	if (validate_map_requirements(game) == -1)
		return (-1);
	game->map.cols = get_max_row_length(game);
	if (game->map.cols <= 0)
		return (print_err("Invalid map: no columns found"));
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

/*	processes each line from file via process_single_file_line(),
	updates found_non_empty, and frees the leftover when done */
int	handle_lines_loop(int fd, t_game *game, int *found_non_empty)
{
	char	*input_line;
	char	*leftover;
	int		line_processing_status;

	leftover = NULL;
	input_line = get_next_line(fd, &leftover);
	while (input_line != NULL)
	{
		line_processing_status = process_single_file_line(input_line, game,
				found_non_empty);
		if (line_processing_status == -1)
		{
			free(leftover);
			return (-1);
		}
		input_line = get_next_line(fd, &leftover);
	}
	free(leftover);
	return (1);
}

/*	replaces spaces, updates flag if line is non‑empty, calls check_line_type()
	on line, returns processing status or success if no line to be processed*/
int	process_single_file_line(char *line, t_game *game, int *found_non_empty)
{
	char	*processed_line;
	int		line_processing_status;

	if (contains_reserved_chars(line))
	{
		free(line);
		return (print_err("Error: invalid characters found in cub file"));
	}
	processed_line = replace_spaces(line);
	free(line);
	if (processed_line)
	{
		if (processed_line[0] != '\0')
			*found_non_empty = 1;
		line_processing_status = check_line_type(processed_line, game);
		free(processed_line);
		return (line_processing_status);
	}
	return (1);
}
