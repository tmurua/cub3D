/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:55:47 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/22 11:02:14 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

/*	returns 1 if input line begins with a valid header identifier, else -1 */
int	is_valid_header(char *line)
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
	return (-1);
}

/*	processes a single non-empty line from the .cub file;
	trims line, then checks if it begins with a valid header (or map indicator)
	for now, it prints the line if valid, or prints an error message if not
	TODO: Replace printing with proper header and map parsing logic. */
int	process_single_line(char *input_line)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(input_line, " \n\r\t");
	if (!trimmed_line || trimmed_line[0] == '\0')
	{
		free(trimmed_line);
		return (1);
	}
	if (is_valid_header(trimmed_line))
		printf("Line: %s\n", trimmed_line);
	else
	{
		free(trimmed_line);
		return (print_err("Invalid *.cub file"));
	}
	free(trimmed_line);
	return (1);
}

/*	opens the .cub file using open_cub_file(), reads it line by line, and
	processes each non-empty line using process_single_line();
	frees each line after processing and returns 1 on success, -1 on failure
	TODO: Integrate header processing and map layout parsing. */
int	parse_map(t_game *game, char *filename)
{
	int		fd;
	char	*input_line;
	int		result;

	(void)game; /* remove this once 'game' is used for storage */
	fd = open_cub_file(filename);
	if (fd < 0)
		return (-1);
	input_line = get_next_line(fd);
	while (input_line != NULL)
	{
		result = process_single_line(input_line);
		free(input_line);
		if (result == -1)
		{
			close(fd);
			return (-1);
		}
		input_line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
