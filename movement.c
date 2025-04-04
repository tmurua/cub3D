/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsternbe <tsternbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:01:35 by tsternbe          #+#    #+#             */
/*   Updated: 2025/04/04 13:25:17 by tsternbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#include "../../include/cubthreed.h"

// pre-selector to call the correct movement function
// depending on which move states are positive
void	handle_input(t_data *d)
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
}

// Moves player forwards or backwards, while first checking if the position
// that will be reached == 0, meaning, is empty. The speed is multiplied
// by the frame_time to make movement smooth, regardless how long time
// it took to calculate each frame
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

// strafes sideways like a crab, while first checking if the position that will
// be reached == 0, meaning, is empty. dir says if moving right or left.
void	strafe(t_data *d, int dir)
{
	double	m_speed;

	m_speed = d->frame_time * 4.0;
	if (d->map[(int)(d->pos_x + d->plane_x * m_speed
			* dir)][(int)d->pos_y] == 0)
		d->pos_x += d->plane_x * m_speed * dir;
	if (d->map[(int)d->pos_x][(int)(d->pos_y + d->plane_y * m_speed
		* dir)] == 0)
		d->pos_y += d->plane_y * m_speed * dir;
}

// turns left or right around the position where player is standing,
// changing direction but not position
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
