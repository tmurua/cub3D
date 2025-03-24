/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:17:52 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/24 11:03:25 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*	reads next line from the file descriptor 'fd'
	returns the line (including newline, if present) and stores any leftover
	characters for the next call; returns NULL on error or end-of-file */
char	*get_next_line(int fd)
{
	static char	*left_c;
	char		*current_line;
	char		*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(left_c);
		free(buffer);
		left_c = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	current_line = read_concatenate_line(fd, left_c, buffer);
	free(buffer);
	if (!current_line)
		return (NULL);
	left_c = set_leftover_chars(current_line);
	return (current_line);
}

/*	reads from 'fd' into 'buffer' and concatenates it with any leftover string
	from previous calls ('left_c'); reading stops when a newline is found or
	when end-of-file is reached; returns the concatenated string */
char	*read_concatenate_line(int fd, char *left_c, char *buffer)
{
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(left_c);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!left_c)
			left_c = ft_strdup("");
		tmp = left_c;
		left_c = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (left_c);
}

/*	finds the newline in 'current_line' and extracts the remaining substring
	(if any) after the newline to be used in the next call
	it also null-terminates 'current_line' right after the newline
	returns the leftover string */
char	*set_leftover_chars(char *current_line)
{
	ssize_t	i;
	char	*leftover;

	i = 0;
	while (current_line[i] != '\n' && current_line[i] != '\0')
		i++;
	if (current_line[i] == '\0')
		return (NULL);
	leftover = ft_substr(current_line, i + 1, ft_strlen(current_line) - i);
	if (*leftover == '\0')
	{
		free(leftover);
		leftover = NULL;
	}
	current_line[i + 1] = '\0';
	return (leftover);
}
