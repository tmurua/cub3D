/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:53:30 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/03 16:57:18 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubthreed.h"
#include "../../include/cub3D.h"

/*	determines initial orientation based on player's parsed orientation */
int	set_initial_orientation(t_data *d, char orientation)
{
	if (orientation == 'N')
		set_north(d);
	else if (orientation == 'S')
		set_south(d);
	else if (orientation == 'E')
		set_east(d);
	else if (orientation == 'W')
		set_west(d);
	else
	{
		print_err("Invalid player orientation");
		return (-1);
	}
	return (1);
}

void	set_north(t_data *d)
{
	d->dir_x = -1;
	d->dir_y = 0;
	d->plane_x = 0;
	d->plane_y = 0.66;
}

void	set_south(t_data *d)
{
	d->dir_x = 1;
	d->dir_y = 0;
	d->plane_x = 0;
	d->plane_y = -0.66;
}

void	set_east(t_data *d)
{
	d->dir_x = 0;
	d->dir_y = 1;
	d->plane_x = 0.66;
	d->plane_y = 0;
}

void	set_west(t_data *d)
{
	d->dir_x = 0;
	d->dir_y = -1;
	d->plane_x = -0.66;
	d->plane_y = 0;
}
