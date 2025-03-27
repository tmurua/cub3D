/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:17:52 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/27 15:28:33 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*	reads next line from 'fd' using leftover as an in/out parameter;
	returns next line (including newline, if present) or NULL on error/EOF */
char	*get_next_line(int fd, char **leftover)
{
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		free(*leftover);
		*leftover = NULL;
		return (NULL);
	}
	if (!*leftover)
		*leftover = ft_strdup("");
	line = read_until_newline(fd, *leftover);
	if (!line || ft_strlen(line) == 0)
	{
		free(line);
		free(*leftover);
		*leftover = NULL;
		return (NULL);
	}
	return (process_leftover(line, leftover));
}

/*	creates a duplicate of init_str and then calls append_until_newline()
	to read and concatenate data until a newline or EOF is encountered;
	returns the concatenated string or NULL on error */
char	*read_until_newline(int fd, char *init_str)
{
	char	*line;

	line = ft_strdup(init_str);
	if (!line)
		return (NULL);
	return (append_until_newline(fd, line));
}

/*	allocates a buffer and reads from fd, concatenating data to 'line'
	until a newline is found or EOF is reached; returns updated 'line'
	(which may contain a newline) or NULL on error */
char	*append_until_newline(int fd, char *line)
{
	char		*buffer;
	ssize_t		bytes_read;
	char		*tmp;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(line, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		tmp = line;
		line = ft_strjoin(line, buffer);
		free(tmp);
	}
	free(buffer);
	return (line);
}

/*	given a line that was just read, it finds the \n; if found, it duplicates
	the part after the \n into *leftover and truncates line after the newline;
	otherwise, it frees *leftover and sets it to NULL */
char	*process_leftover(char *line, char **leftover)
{
	char	*newline_ptr;
	char	*tmp;

	newline_ptr = ft_strchr(line, '\n');
	if (newline_ptr)
	{
		tmp = ft_strdup(newline_ptr + 1);
		free(*leftover);
		*leftover = tmp;
		newline_ptr[1] = '\0';
	}
	else
	{
		free(*leftover);
		*leftover = NULL;
	}
	return (line);
}
