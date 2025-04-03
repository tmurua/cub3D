/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:39:43 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/03 20:05:18 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/*	checks if a color header is duplicated, then parses the color line,
	sets the header flag to indicate current color header was parsed */
int	handle_color_hdr(char *line, int *color_field, int *header_flag)
{
	if (*header_flag)
		return (print_err("Found duplicated header"));
	if (parse_color_line(line, color_field) == -1)
		return (-1);
	*header_flag = 1;
	return (1);
}

/*	expects a line like "F 155,155,155" or "C 204,229,255"; skips identifier,
	splits it by commas; checks if there are exactly three numeric parts,
	and combines them into a single int, color_field, stored in game->color */
int	parse_color_line(char *line, int *color_field)
{
	char	*color_line;
	char	**tokens;
	int		red;
	int		green;
	int		blue;

	color_line = ft_strtrim(line + 2, " ");
	if (!color_line)
		return (print_err("Color header: allocation failed"));
	tokens = ft_split(color_line, ',');
	free(color_line);
	if (!tokens)
		return (print_err("Color header: allocation failed"));
	if (validate_color_tokens(tokens, &red, &green, &blue) == -1)
		return (-1);
	*color_field = (red << 16) | (green << 8) | blue;
	ft_free_strs(tokens);
	return (1);
}

/*	checks that tokens contains exactly three numeric strings;
	converts each token to an integer and verifies they are between 0 and 255;
	on success, stores the values in red, green, and blue and returns 1;
	on error, frees tokens and returns -1 */
int	validate_color_tokens(char **tokens, int *red, int *green, int *blue)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	if (i != 3)
	{
		ft_free_strs(tokens);
		return (print_err("Color header: expected 3 (RGB) components"));
	}
	*red = ft_atoi(tokens[0]);
	*green = ft_atoi(tokens[1]);
	*blue = ft_atoi(tokens[2]);
	if (*red < 0 || *red > 255 || *green < 0 || *green > 255 || *blue < 0
		|| *blue > 255)
	{
		ft_free_strs(tokens);
		return (print_err("Color header: values must be between 0 and 255"));
	}
	return (1);
}

void	ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
