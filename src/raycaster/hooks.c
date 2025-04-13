/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:55:52 by tsternbe          #+#    #+#             */
/*   Updated: 2025/04/13 21:06:32 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubthreed.h"
#include "../../include/cub3D.h"

/*	computes the 1D array index given 2D coordinates (x, y) using number of cols
	stored in d->map_cols; returns the computed index */
int	get_map_index(t_data *d, int x, int y)
{
	return (x * d->map_cols + y);
}

/*	converts game->map.lines into a dynamically allocated integer array
	'1' becomes 1 (wall) and any other valid character becomes 0 (open space)
	returns pointer to new integer array or NULL on allocation failure */
int	*convert_parsed_map(t_game *game)
{
	int	*new_map;
	int	row;
	int	col;
	int	index;

	new_map = malloc(game->map.rows * game->map.cols * sizeof(int));
	if (!new_map)
	{
		perror("Failed to allocate memory for converted map");
		return (NULL);
	}
	row = 0;
	while (row < game->map.rows)
	{
		col = 0;
		while (col < game->map.cols)
		{
			index = row * game->map.cols + col;
			if (game->map.lines[row][col] == '1')
				new_map[index] = 1;
			else
				new_map[index] = 0;
			col++;
		}
		row++;
	}
	return (new_map);
}

/*	copies dimensions from parsed map and converts the array of strings
	into a 1D integer array stored in d->map */
void	load_parsed_map(t_data *d, t_game *game)
{
	d->map_rows = game->map.rows;
	d->map_cols = game->map.cols;
	d->map = convert_parsed_map(game);
	if (!d->map)
	{
		perror("Error converting parsed map");
		exit(EXIT_FAILURE);
	}
}

int	handle_keypress(int keycode, t_data *d)
{
	if (keycode == XK_Escape)
		destroy(d);
	if (keycode == XK_r)
	{
		d->running_speed = 0.0;
		if (d->radio_car == 0)
			d->radio_car = 1;
		else
			d->radio_car = 0;
	}
	if (keycode == XK_a)
		d->move[3] = 1;
	if (keycode == XK_s || keycode == XK_Down)
		d->move[1] = 1;
	if (keycode == XK_d)
		d->move[2] = 1;
	if (keycode == XK_w || keycode == XK_Up)
		d->move[0] = 1;
	if (keycode == XK_Right)
		d->move[4] = 1;
	if (keycode == XK_Left)
		d->move[5] = 1;
	return (0);
}

int	handle_keyrelease(int keycode, t_data *d)
{
	if (keycode == XK_a)
		d->move[3] = 0;
	if (keycode == XK_s || keycode == XK_Down)
		d->move[1] = 0;
	if (keycode == XK_d)
		d->move[2] = 0;
	if (keycode == XK_w || keycode == XK_Up)
		d->move[0] = 0;
	if (keycode == XK_Right)
		d->move[4] = 0;
	if (keycode == XK_Left)
		d->move[5] = 0;
	return (0);
}
