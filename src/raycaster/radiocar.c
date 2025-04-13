/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radiocar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:14:17 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/13 21:09:31 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#include "../../include/cubthreed.h"

int	handle_mouse_scroll(int button, int x, int y, t_data *d)
{
	(void)x;
	(void)y;
	if (button == 4)
		d->running_speed += 0.1;
	else if (button == 5)
		d->running_speed -= 0.1;
	if (d->running_speed < 0.1)
		d->running_speed = 0.0;
	return (0);
}

int	steer_car(t_data *d)
{
	double	m_speed;
	double	r_speed;
	double	old_dir_x;
	double	old_plane_x;

	if (d->running_speed > 0.0)
	{
		m_speed = d->running_speed * d->frame_time * 4.0;
		if (d->map[get_map_index(d, (int)(d->pos_x + d->dir_x * m_speed),
				(int)d->pos_y)] == 0)
			d->pos_x += d->dir_x * m_speed;
		if (d->map[get_map_index(d, (int)d->pos_x, (int)(d->pos_y + d->dir_y
					* m_speed))] == 0)
			d->pos_y += d->dir_y * m_speed;
	}
	if (d->mouse_offset < -0.1 || d->mouse_offset > 0.1)
	{
		r_speed = d->frame_time * 2.0 * d->mouse_offset * -1.0;
		old_dir_x = d->dir_x;
		d->dir_x = d->dir_x * cos(r_speed) - d->dir_y * sin(r_speed);
		d->dir_y = old_dir_x * sin(r_speed) + d->dir_y * cos(r_speed);
		old_plane_x = d->plane_x;
		d->plane_x = d->plane_x * cos(r_speed) - d->plane_y * sin(r_speed);
		d->plane_y = old_plane_x * sin(r_speed) + d->plane_y * cos(r_speed);
	}
	return (0);
}
