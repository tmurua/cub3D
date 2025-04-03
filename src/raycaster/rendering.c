/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:11:44 by tsternbe          #+#    #+#             */
/*   Updated: 2025/04/03 21:20:46 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#include "../../include/cubthreed.h"

void	draw_walls(t_data *d)
{
	d->x = 0;
	while (d->x < SCREENWIDTH)
	{
		d->ray_dir_x = d->dir_x + d->plane_x * (2 * d->x / (double)SCREENWIDTH
				- 1);
		d->ray_dir_y = d->dir_y + d->plane_y * (2 * d->x / (double)SCREENWIDTH
				- 1);
		d->map_x = (int)d->pos_x;
		d->map_y = (int)d->pos_y;
		if (d->ray_dir_x == 0)
			d->delta_dist_x = 1e30;
		else
			d->delta_dist_x = fabs(1.0 / d->ray_dir_x);
		if (d->ray_dir_y == 0)
			d->delta_dist_y = 1e30;
		else
			d->delta_dist_y = fabs(1.0 / d->ray_dir_y);
		calc_step_and_sidedist(d);
		digital_differential_analyzer(d);
		calc_tex_column(d);
		d->x++;
	}
}

void	calc_step_and_sidedist(t_data *d)
{
	if (d->ray_dir_x < 0)
	{
		d->step_x = -1;
		d->side_dist_x = (d->pos_x - d->map_x) * d->delta_dist_x;
	}
	else
	{
		d->step_x = 1;
		d->side_dist_x = (d->map_x + 1.0 - d->pos_x) * d->delta_dist_x;
	}
	if (d->ray_dir_y < 0)
	{
		d->step_y = -1;
		d->side_dist_y = (d->pos_y - d->map_y) * d->delta_dist_y;
	}
	else
	{
		d->step_y = 1;
		d->side_dist_y = (d->map_y + 1.0 - d->pos_y) * d->delta_dist_y;
	}
}

void	draw_sky_and_floor(t_data *d)
{
	int	y;
	int	x;
	int	color;
	int	pixel_pos;

	y = 0;
	while (y < SCREENHEIGHT)
	{
		if (y < SCREENHEIGHT / 2)
			color = d->g.color.floor;
		else
			color = d->g.color.ceiling;
		x = 0;
		while (x < SCREENWIDTH)
		{
			pixel_pos = y * d->ll + x * d->x_step;
			*(int *)(d->addr + pixel_pos) = color;
			x++;
		}
		y++;
	}
}

void	render_image(t_data *d)
{
	d->time = now();
	d->frame_time = (d->time - d->old_time) / 1000000.0;
	if (d->frame_time > 0.01667)
		d->frame_time = 0.01667;
	if (d->radio_car == 1)
	{
		d->mouse_offset = (d->mouse_x - d->screen_center) / d->screen_center;
		steer_car(d);
	}
	else
		handle_input(d);
	draw_sky_and_floor(d);
	draw_walls(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	d->old_time = d->time;
}

int	render_image_wrapper(void *param)
{
	t_data	*d;
	int		x;
	int		y;

	d = (t_data *)param;
	mlx_mouse_get_pos(d->mlx, d->win, &x, &y);
	(void)y;
	d->mouse_x = x;
	render_image(d);
	return (0);
}
