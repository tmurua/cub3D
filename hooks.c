/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsternbe <tsternbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:55:52 by tsternbe          #+#    #+#             */
/*   Updated: 2025/04/04 11:16:09 by tsternbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubthreed.h"
#include "../../include/cub3D.h"

/*	copies parsed game->map.lines into raycaster's map array d->map
	each char '1' is converted to 1 (wall) and any other chars to 0 (floor)
void	load_parsed_map(t_data *d, t_game *game)
{
	(void)game;
	int worldMap[map_width][map_height] =
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
	for (int x = 0; x < map_width; x++)
	{
		for (int y = 0; y < map_height; y++)
		{
			d->map[x][y] = worldMap[x][y];
		}
	}
}*/


// reads when a key is pressed. It either calls for an event
// (radiocar switch and Esc) or changes the state of one of the move[6] var.
// This is later used for controlling movement. Several keys can
// trigger the same move state, for example w and Up-arrow both changes move[0]
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

// reads if one of the control keys has been released. This changes one of the
// move[6] states to 0. Which is later used for controlling movement
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
