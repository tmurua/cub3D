/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:55:52 by tsternbe          #+#    #+#             */
/*   Updated: 2025/04/03 18:20:16 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubthreed.h"
#include "../../include/cub3D.h"

/*	copies parsed game->map.lines into raycaster's map array d->map
	each char '1' is converted to 1 (wall) and any other chars to 0 (floor) */
void	load_parsed_map(t_data *d, t_game *game)
{
	(void)game;
	int worldMap[mapWidth][mapHeight] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	for (int x = 0; x < mapWidth; x++)
	{
		for (int y = 0; y < mapHeight; y++)
		{
			d->map[x][y] = worldMap[x][y];
		}
	}
}
// void	load_parsed_map(t_data *d, t_game *game)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	while (x < game->map.rows)
// 	{
// 		y = 0;
// 		while (y < game->map.cols)
// 		{
// 			d->map[x][y] = game->map.lines[x][y];
// 			y++;
// 		}
// 		x++;
// 	}
// }


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
