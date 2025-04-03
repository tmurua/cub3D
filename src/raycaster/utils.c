/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:24:07 by tsternbe          #+#    #+#             */
/*   Updated: 2025/04/03 19:26:11 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubthreed.h"
#include "../../include/cub3D.h"

/* returns timestamp of now from Epoch in microseconds */
long long	now(void)
{
	long long		us;
	struct timeval	time;

	gettimeofday(&time, NULL);
	us = ((time.tv_sec * 1000000) + time.tv_usec);
	return (us);
}


int	initialize_img(t_data *d)
{
	d->mlx = mlx_init();
	if (d->mlx == NULL)
	{
		perror("Failed to initialize mlx");
		return (1);
	}
	d->win = mlx_new_window(d->mlx, screenWidth, screenHeight, "raycaster");
	if (d->win == NULL)
	{
		free(d->win);
		perror("Failed to open window");
		return (2);
	}
	d->img = mlx_new_image(d->mlx, screenWidth, screenHeight);
	if (d->img == NULL)
	{
		free(d->img);
		free(d->win);
		perror("Failed to create image");
		return (3);
	}
	d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->ll, &d->end);
	d->x_step = d->bpp / 8;
	return (0);
}

int	destroy(t_data *d)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free_texture(d->texture[i], texHeight);
		i++;
	}
	if (d->img)
		mlx_destroy_image(d->mlx, d->img);
	if (d->win)
		mlx_destroy_window(d->mlx, d->win);
	if (d->mlx)
	{
		mlx_destroy_display(d->mlx);
		free(d->mlx);
	}
	exit(0);
	return (0);
}
