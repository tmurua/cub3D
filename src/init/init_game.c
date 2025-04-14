/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:27:03 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/14 12:32:49 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#include "../../include/cubthreed.h"

int	init_game(t_game *game)
{
	t_data	d;

	if (initialize_data(&d, game) != 0)
		return (-1);
	if (initialize_img(&d) != 0)
		return (-1);
	load_parsed_map(&d, game);
	textures(&d, game);
	copy_colors(&d, game);
	clean_game(game);
	mlx_hook(d.win, DestroyNotify, StructureNotifyMask, &destroy, &d);
	mlx_hook(d.win, KeyPress, KeyPressMask, &handle_keypress, &d);
	mlx_hook(d.win, KeyRelease, KeyReleaseMask, &handle_keyrelease, &d);
	mlx_hook(d.win, ButtonPress, ButtonPressMask, &handle_mouse_scroll, &d);
	mlx_loop_hook(d.mlx, &render_image_wrapper, &d);
	mlx_loop(d.mlx);
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
	d->screen_center = SCREENWIDTH / 2.0;
	d->mouse_x = SCREENWIDTH / 2;
	d->radio_car = 0;
	return (0);
}

void	copy_colors(t_data *d, t_game *game)
{
	d->g.color.floor = game->color.floor;
	d->g.color.ceiling = game->color.ceiling;
}
