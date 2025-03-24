/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:55:47 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/24 16:40:48 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/* opens .cub, check if file is empty, reads each line, and processes it */
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
	return (1);
}
/* ft lines: 15 */

/*	read every line from file, trim whitespace from each line, update flag
	if a non‑empty line is encountered, and then process each line */
int	process_file_lines(int fd, t_game *game, int *found_non_empty)
{
	char	*input_line;
	char	*trimmed_line;
	int		result;

	input_line = get_next_line(fd);
	while (input_line != NULL)
	{
		trimmed_line = ft_strtrim(input_line, " \n\r\t");
		free(input_line);
		if (trimmed_line)
		{
			if (trimmed_line[0] != '\0')
				*found_non_empty = 1;
			result = process_line(trimmed_line, game);
			free(trimmed_line);
			if (result == -1)
				return (-1);
		}
		input_line = get_next_line(fd);
	}
	return (1);
}
/* ft lines: 21 */

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
/* ft lines: 8 */

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
/* ft lines: 9 */
