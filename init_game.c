/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsternbe <tsternbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:27:03 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/04 13:25:56 by tsternbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#include "../../include/cubthreed.h"

int	init_game(t_game *game)
{
	t_data	d;

	if (initialize_data(&d, game) != 0)
	{
		printf("Failed initialize_data\n");
		return (-1);
	}
	if (initialize_img(&d) != 0)
	{
		printf("Failed initialize_img\n");
		return (-1);
	}
	if (load_parsed_map(&d, game) != 0)
	{
		printf("Failed load_parsed_map\n");
		return (-1);
	}
	textures(&d, game);
//	copy_colors(&d, game);
	mlx_hook(d.win, DestroyNotify, StructureNotifyMask, &destroy, &d);
	mlx_hook(d.win, KeyPress, KeyPressMask, &handle_keypress, &d);
	mlx_hook(d.win, KeyRelease, KeyReleaseMask, &handle_keyrelease, &d);
	mlx_hook(d.win, ButtonPress, ButtonPressMask, &handle_mouse_scroll, &d);
	mlx_loop_hook(d.mlx, &render_image_wrapper, &d);
	mlx_loop(d.mlx);
//	cleanup_resources(d); WE NEED A FUNCTION TO FREE ALL
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
	printf("initialize_data executed\n");
	return (0);
}

// this was so small I stuck it in load_parsed_map
/* void	copy_colors(t_data *d, t_game *game)
{
	d->floor = game->color.floor;
	d->ceiling = game->color.ceiling;
} */

int	load_parsed_map(t_data *d, t_game *g)
{
	int	mx;
	int	my;

	d->floor = g->color.floor;
	d->ceiling = g->color.ceiling;
	d->map_width = g->map.cols;
	d->map_height = g->map.rows;
	d->map = allocate_map(d);
	if (!d->map)
		return (-1);
	mx = 0;
	while (mx < d->map_width)
	{
		my = 0;
		while (my < d->map_height)
		{
			d->map[mx][my] = g->map.lines[mx][my];
			my++;
		}
		mx++;
	}
	printf("load_parsed_map executed\n");
	return (0);
}

int**	allocate_map(t_data *d)
{
	int**	map;
	int		i;

	map = malloc(d->map_width * sizeof(int*));
	if (!map)
		return(NULL);
	i = 0;
	while (i < d->map_width)
	{
		map[i] = malloc(d->map_height * sizeof(int));
		if (!map[i])
		{
			while (i > 0)
			{
				free(map[i - 1]);
				i--;
			}
			free(map);
			return (NULL);
		}
		i++;
	}
	printf("allocate_map executed\n");
	return (map);
}
