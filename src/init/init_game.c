/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:27:03 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/03 17:03:34 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubthreed.h"
#include "../../include/cub3D.h"

int	init_game(t_game *game)
{
	t_data	d;

	if (initialize_data(&d, game) != 0)
		return (-1);
	if (initialize_img(&d) != 0)
		return (-1);
	save_map(&d); //TODO
	textures(&d); //TODO
	mlx_hook(d.win, DestroyNotify, StructureNotifyMask, &destroy, &d); //TODO
	mlx_hook(d.win, KeyPress, KeyPressMask, &handle_keypress, &d); //TODO
	mlx_hook(d.win, KeyRelease, KeyReleaseMask, &handle_keyrelease, &d); //TODO
	mlx_hook(d.win, ButtonPress, ButtonPressMask, &handle_mouse_scroll, &d); //TODO
	mlx_loop_hook(d.mlx, &render_image_wrapper, &d); //TODO
	mlx_loop(d.mlx); //TODO
	return (1);
}

int	initialize_data(t_data *d, t_game *game)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		d->move[i] = 0;
		i++;
	}
	d->pos_x = game->player.x;
	d->pos_y = game->player.y;
	if (set_initial_orientation(d, game->player.orientation) == -1)
		return (-1);
	d->time = now();
	d->old_time = d->time;
	d->running_speed = 0;
	d->screen_center = screenWidth / 2.0;
	d->mouse_x = screenWidth / 2;
	d->radio_car = 0;
	return (0);
}
