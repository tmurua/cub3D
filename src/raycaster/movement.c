/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:01:35 by tsternbe          #+#    #+#             */
/*   Updated: 2025/04/03 15:32:24 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubthreed.h"
#include "../../include/cub3D.h"

int	handle_input(t_data *d)
{
	if (d->move[0])
		move(d, 1);
	if (d->move[1])
		move(d, -1);
	if (d->move[3])
		strafe(d, -1);
	if (d->move[2])
		strafe(d, 1);
	if (d->move[5])
		pivot(d, 1);
	if (d->move[4])
		pivot(d, -1);
	return (0);
}

void	move(t_data *d, int dir)
{
	double	m_speed;

	m_speed = d->frame_time * 4.0;
	if (dir == 1)
	{
		if (d->map[(int)(d->pos_x + d->dir_x * m_speed)][(int)d->pos_y] == 0)
			d->pos_x += d->dir_x * m_speed;
		if (d->map[(int)d->pos_x][(int)(d->pos_y + d->dir_y * m_speed)] == 0)
			d->pos_y += d->dir_y * m_speed;
	}
	else
	{
		if (d->map[(int)(d->pos_x - d->dir_x * m_speed)][(int)d->pos_y] == 0)
			d->pos_x -= d->dir_x * m_speed;
		if (d->map[(int)d->pos_x][(int)(d->pos_y - d->dir_y * m_speed)] == 0)
			d->pos_y -= d->dir_y * m_speed;
	}
}

void	strafe(t_data *d, int dir)
{
	double	m_speed;

	m_speed = d->frame_time * 4.0;
	if (d->map[(int)(d->pos_x + d->plane_x * m_speed * dir)][(int)d->pos_y] == 0)
		d->pos_x += d->plane_x * m_speed * dir;
	if (d->map[(int)d->pos_x][(int)(d->pos_y + d->plane_y * m_speed * dir)] == 0)
		d->pos_y += d->plane_y * m_speed * dir;
}

void	pivot(t_data *d, int pivot)
{
	double	r_speed;
	double	old_dir_x;
	double	old_plane_x;

	r_speed = d->frame_time * 2.0 * pivot;
	old_dir_x = d->dir_x;
	d->dir_x = d->dir_x * cos(r_speed) - d->dir_y * sin(r_speed);
	d->dir_y = old_dir_x * sin(r_speed) + d->dir_y * cos(r_speed);
	old_plane_x = d->plane_x;
	d->plane_x = d->plane_x * cos(r_speed) - d->plane_y * sin(r_speed);
	d->plane_y = old_plane_x * sin(r_speed) + d->plane_y * cos(r_speed);
}
