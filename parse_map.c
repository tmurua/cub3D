/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:55:47 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/20 19:41:24 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* checks if 'filename' ends with the ".cub" extension */
int	has_cub_extension(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 4, ".cub", 4) == 0);
}

/* validates that the file has a ".cub" extension and then opens it */
int	open_cub_file(const char *filename)
{
	int	fd;

	if (!has_cub_extension(filename))
	{
		fprintf(stderr, "Error: File must have a .cub extension\n");
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		perror("Error opening scene file");
	return (fd);
}

/*	returns 1 if the given (trimmed) line begins with a valid header identifier
	or starts with '1' (indicating a map row), else returns 0. */
int	is_valid_header(const char *line)
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

/*	processes a single non-empty line from the .cub file.
	trims line, then checks if it begins with a valid header (or map indicator)
	for now, it prints the line if valid, or prints an error message if not
	TODO: Replace printing with proper header and map parsing logic. */
void	process_single_line(const char *raw)
{
	char	*line;

	line = ft_strtrim(raw, " \n\r\t");
	if (!line || line[0] == '\0')
	{
		free(line);
		return ;
	}
	if (is_valid_header(line))
		printf("Line: %s\n", line);
	else
		printf("Invalid *.cub file\n");
	free(line);
}

/*	opens the .cub file using open_cub_file(), reads it line by line,
	and for each non-empty line calls process_single_line() to process it;
	frees each line after processing and returns 1 on success, 0 on failure
	TODO: Integrate header processing and map layout parsing. */
int	parse_map(t_game *game, const char *filename)
{
	int		fd;
	char	*line;

	(void)game; /* Remove this once 'game' is used for storage */
	fd = open_cub_file(filename);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		/* process_single_line() now trims the line internally */
		process_single_line(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
