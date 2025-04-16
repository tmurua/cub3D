/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 07:04:20 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/16 19:53:20 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	print_err(char *str_err)
{
	ft_putstr_fd("Error\n", 2);
	if (str_err)
		ft_putendl_fd(str_err, 2);
	return (-1);
}

int	free_and_return(char *ptr, int ret)
{
	free(ptr);
	return (ret);
}

int	contains_reserved_chars(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '@' || line[i] == '^')
			return (1);
		i++;
	}
	return (0);
}
