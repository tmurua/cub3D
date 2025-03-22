/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:55:47 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/22 15:37:58 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* opens .cub file, reads each line, and processes it using process_line() */
int	parse_map(t_game *game, char *filename)
{
	int		fd;
	char	*input_line;
	int		result;

	fd = open_cub_file(filename);
	if (fd < 0)
		return (-1);
	input_line = get_next_line(fd);
	while (input_line != NULL)
	{
		result = process_line(input_line, game);
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
