/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsternbe <tsternbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:11:44 by tsternbe          #+#    #+#             */
/*   Updated: 2025/04/04 13:24:26 by tsternbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#include "../../include/cubthreed.h"

// Is called from mlx_loop_hook. Reads the position of mouse, saves mouse_x
// (for radiocar steering) and then calls render_image.
// The wrapper is necessary to call render_image from mlx_loop_hook
// with struct d
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

// Function to manage movement and rendering.
// Calculates frame_time, to ensure smooth movement
// calls either radio_car steering or key based movement to change player pos
// draw floor and ceiling to img, draw walls to img, put img to window
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
	draw_floor_and_ceiling(d);
	draw_walls(d);
	// THIS IS WHERE IT SEGFAULTS
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	d->old_time = d->time;
}

// divides the window in two horizontal blocks and fills them with
// floor and ceiling color. Walls are drawn on top of this
// ensures all pixels from previous frame are removed
// plus is the fastest way to render floor and ceiling
void	draw_floor_and_ceiling(t_data *d)
{
	int	y;
	int	x;
	int	color;
	int	pixel_pos;

	y = 0;
	while (y < SCREENHEIGHT)
	{
		if (y < SCREENHEIGHT / 2)
			color = d->floor;
		else
			color = d->ceiling;
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

// Function for drawing the walls. Sky and floor has already been drawn
// as two color blocks, for efficient rendering. Walls are drawn on top
// d->x iterates through all x columns of screen from left to right
// ray directions are calculated depending on player direction
// map_x and map_y are which grid the player is. This is for the DDA
// if ray direction is 0, delta_dist is set to very high to avoid / zero
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

// Calculates how the ray is stepping through the map grid. step_x and _y
// are direction of step. delta_dist is distance from last step to next grid
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




