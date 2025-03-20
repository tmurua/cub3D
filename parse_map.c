/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:55:47 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/20 16:31:18 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* should read map file (*.cub), parse texture paths, floor/ceiling, colors, map
layout and store everything in the t_game game structure
for now, implementation only opens the file and prints each non-empty line
TODO: add code to validate the format and store the parsed data */
int	parse_map(t_game *game, const char *filename)
{
	int		fd;
	char	*line;

	(void)game;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening scene file");
		return (0);
	}
	/* read the file line by line */
	while ((line = get_next_line(fd)))
	{
		/* skip empty lines */
		if (line[0] != '\0')
		{
			/*	for now, it only prints the line
				TODO: replace it with proper parsing logic
				i.e. check if line starts with "NO", "SO", "WE", "EA", "F", "C",
				or if it is part of the map. */
			printf("Line: %s\n", line);
		}
		free(line);
	}
	close(fd);
	return (1);
}

