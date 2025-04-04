/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsternbe <tsternbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:04:52 by tsternbe          #+#    #+#             */
/*   Updated: 2025/04/04 10:09:36 by tsternbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubthreed.h"
#include "../../include/cub3D.h"

// Checks which wall a ray hit, by comparing side, and then step_x or step_y.
// side says if the wall is vertical or horizontal, step_x and step_y in
// which direction the ray was moving. This decides which texture to use (tex)
int	which_texture(int side, int step_y, int step_x)
{
	int	tex;

	if (side == 1)
	{
		if (step_y > 0)
			tex = 0;
		else
			tex = 1;
	}
	else
	{
		if (step_x > 0)
			tex = 2;
		else
			tex = 3;
	}
	return (tex);
}

// perp_wall_d is the perpendicular distance from the camera plane to the wall
// which is hit. This is used instead of ray distance, to avoid fish-eye effect
// wall_x says where exactly on the wall the ray hits.
// Using floor on wall_x takes away the decimals and gives pixel column in int
// tex_x is which x column in the texture to use.
int	tex_x(t_data *d, double perp_wall_d)
{
	double	wall_x;
	int		tex_x;

	if (d->side == 0)
		wall_x = d->pos_y + perp_wall_d * d->ray_dir_y;
	else
		wall_x = d->pos_x + perp_wall_d * d->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)TEXWIDTH);
	if (d->side == 0 && d->ray_dir_x > 0)
		tex_x = TEXWIDTH - tex_x - 1;
	if (d->side == 1 && d->ray_dir_y < 0)
		tex_x = TEXWIDTH - tex_x - 1;
	return (tex_x);
}

// draws a column of texture the height of the wall into the image buffer
// x_step is how many bytes it jumps in the array per pixel
// This is precalculated to save rendering time
void	tex_column_to_img(t_data *d, int line_h, int draw_start, int draw_end)
{
	double	step;
	double	tex_pos;
	int		y;
	int		pixel_pos;
	int		tex_y;

	step = 1.0 * TEXHEIGHT / line_h;
	tex_pos = (draw_start - SCREENHEIGHT / 2 + line_h / 2) * step;
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos & (TEXHEIGHT - 1);
		tex_pos += step;
		pixel_pos = y * d->ll + d->x * d->x_step;
		*(int *)(d->addr + pixel_pos) = d->texture[d->tex][tex_y][d->tex_x];
		y++;
	}
}

// calculates height of wall, and how high up to start drawing
// and where to stop before calling tex_column_to_img
void	calc_tex_column(t_data *d)
{
	int		line_h;
	int		draw_start;
	int		draw_end;
	double	perp_wall_d;

	if (d->side == 0)
		perp_wall_d = (d->side_dist_x - d->delta_dist_x);
	else
		perp_wall_d = (d->side_dist_y - d->delta_dist_y);
	line_h = (int)(SCREENHEIGHT / perp_wall_d);
	d->tex = which_texture(d->side, d->step_y, d->step_x);
	d->tex_x = tex_x(d, perp_wall_d);
	draw_start = -line_h / 2 + SCREENHEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_h / 2 + SCREENHEIGHT / 2;
	if (draw_end >= SCREENHEIGHT)
		draw_end = SCREENHEIGHT - 1;
	tex_column_to_img(d, line_h, draw_start, draw_end);
}

// the DDA algorith that efficiently lets each ray step through the map grid
// and checks if it hits a wall only as it passes a grid line
void	digital_differential_analyzer(t_data *d)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (d->side_dist_x < d->side_dist_y)
		{
			d->side_dist_x += d->delta_dist_x;
			d->map_x += d->step_x;
			d->side = 0;
		}
		else
		{
			d->side_dist_y += d->delta_dist_y;
			d->map_y += d->step_y;
			d->side = 1;
		}
		if (d->map[d->map_x][d->map_y] > 0)
			hit = 1;
	}
}
