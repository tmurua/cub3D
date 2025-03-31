#include "raycaster.h"

// returns timestamp of now from Epoch in microseconds
long long	now()
{
	long long		us;
	struct timeval	time;

	gettimeofday(&time, NULL);
	us = ((time.tv_sec * 1000000) + time.tv_usec);
	return (us);
}

int	initialize_data(t_data *data)
{
	int i;

	i = 0;
	while (i < 6)
	{
		data->move[i] = 0;
		i++;
	}
	data->posX = 22;
	data->posY = 12;
	data->dirX = -1;
	data->dirY = 0;
	data->planeX = 0;
	data->planeY = 0.66;
	data->time = now();
	data->oldTime = data->time;
	data->mlx = mlx_init();
	if (data->mlx == NULL)
	{
		perror("Failed to initialize mlx");
		return (1);
	}
	data->win = mlx_new_window(data->mlx, screenWidth, screenHeight, "raycaster");
	if (data->win == NULL)
	{
		free(data->win);
		perror("Failed to open window");
		return (2);
	}
	data->img = mlx_new_image(data->mlx, screenWidth, screenHeight);
	if (data->img == NULL)
	{
		free(data->img);
		free(data->win);
		perror("Failed to create image");
		return (3);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->ll, &data->end);
	data->x_step = data->bpp / 8;
	return (0);
}

/* void	initialize_calc(t_data *data)
{
	data->cameraX = 0;
	data->rayDirX = 0;
	data->rayDirY = 0;
	data->mapX = 0;
	data->mapY = 0;
	data->deltaDistX = 0;
	data->deltaDistY = 0;
	data->perpWallDist = 0;
	data->stepX = 0;
	data->stepY = 0;
	data->hit = 0;
	data->side = 0;
	data->sideDistX = 0;
	data->sideDistY = 0;
	data->lineHeight = 0;
	data->drawStart = 0;
	data->drawEnd = 0;
	data->tex = 0;
	data->wallX = 0;
	data->texX = 0;
	data->step = 0;
	data->texPos = 0;
	data->y = 0;
	data->texY = 0;
	data->pixelPos = 0;
} */

int	destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free_texture(data->texture[i], texHeight);
		i++;
	}
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(0);
	return (0);
}

int rgb_to_int(double r, double g, double b)
{
	int color = 0;
	color |= (int)(b * 255);
	color |= (int)(g * 255) << 8;
	color |= (int)(r * 255) << 16;
	return (color);
}
