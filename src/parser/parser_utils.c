/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:07:35 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/24 16:16:54 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

/* checks duplicate using *hdr_flag, then calls parse_texture_line() */
int	handle_texture_header(char *dup_msg, char *line, int *hdr_flag,
		char **texture_field)
{
	if (*hdr_flag)
		return (print_err(dup_msg));
	if (parse_texture_line(line, texture_field) == -1)
		return (-1);
	*hdr_flag = 1;
	return (1);
}
/* ft lines: 6 */

/* checks duplicate using *hdr_flag, then calls parse_color_line() */
int	handle_color_header(char *dup_msg, char *line, int *hdr_flag,
		int *color_field)
{
	if (*hdr_flag)
		return (print_err(dup_msg));
	if (parse_color_line(line, color_field) == -1)
		return (-1);
	*hdr_flag = 1;
	return (1);
}
/* ft lines: 6 */
