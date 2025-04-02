/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsternbe <tsternbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:55:52 by tsternbe          #+#    #+#             */
/*   Updated: 2025/04/01 14:53:20 by tsternbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubthreed.h"

void save_map(t_data *d)
{
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

int	handle_keypress(int keycode, t_data *d)
{
	if (keycode == XK_Escape)
		destroy(d);
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

int	main(void)
{
	t_data	d;

	if (initialize_data(&d) != 0)
		return (1);
	if (initialize_img(&d) != 0)
		return (2);
	save_map(&d);
	textures(&d);
	mlx_hook(d.win, DestroyNotify, StructureNotifyMask, &destroy, &d);
	mlx_hook(d.win, KeyPress, KeyPressMask, &handle_keypress, &d);
	mlx_hook(d.win, KeyRelease, KeyReleaseMask, &handle_keyrelease, &d);
	mlx_loop_hook(d.mlx, &render_image_wrapper, &d);
	mlx_loop(d.mlx);
	return (0);
}
