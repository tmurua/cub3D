/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 07:04:20 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/03 15:36:41 by tmurua           ###   ########.fr       */
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

void	malloc_error(void)
{
	perror("malloc");
	exit(EXIT_FAILURE);
}

int	free_and_return(char *ptr, int ret)
{
	free(ptr);
	return (ret);
}
