#include "raycaster.h"

// returns timestamp of now from Epoch in us
long long	now()
{
	long long		us;
	struct timeval	time;

	gettimeofday(&time, NULL);
	us = ((time.tv_sec * 1000000) + time.tv_usec);
	return (us);
}

int	initialize(t_data *data)
{
	data->posX = 22;
	data->posY = 12;
	data->dirX = -1;
	data->dirY = 0;
	data->planeX = 0;
	data->planeY = 0.66;
	data->time = now();
	data->oldTime = data->time;
	data->mlx = NULL;
	data->win = NULL;
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
		return (2);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->ll, &data->end);
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		destroy(data);
	else if (keysym == XK_W || keysym == XK_w || keysym == XK_Up)
		attempt_move(data, 0, -1, 0);
	else if (keysym == XK_A || keysym == XK_a)
		attempt_move(data, -1, 0, 0);
	else if (keysym == XK_S || keysym == XK_s || keysym == XK_Down)
		attempt_move(data, 0, 1, 0);
	else if (keysym == XK_D || keysym == XK_d)
		attempt_move(data, 1, 0, 0);
	else if (keysym == XK_Left)
		attempt_move(data, 0, 0, 1);
	else if (keysym == XK_Right)
		attempt_move(data, 0, 0, -1);
	return (0);
}

int	destroy(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(1);
	return (1);
}

void	attempt_move(t_data *data, int m_x, int m_y, int pivot)
{
	double mSpeed = data->frameTime * 5.0;
	double rSpeed = data->frameTime * 3.0;

	// move
	if (m_y != 0 || m_x != 0)
	{
		if(data->map[(int)(data->posX + data->dirX * mSpeed * m_x)][(int)data->posY] == 0)
			data->posX += data->dirX * mSpeed * m_x;
		if(data->map[(int)data->posX][(int)(data->posY + data->dirY * mSpeed * m_y)] == 0)
			data->posY += data->dirY * mSpeed * m_y;
	}
	// rotate
	if (pivot != 0)
	rSpeed = rSpeed * pivot;
	{
		double oldDirX = data->dirX;
		data->dirX = data->dirX * cos(rSpeed) - data->dirY * sin(rSpeed);
		data->dirY = oldDirX * sin(rSpeed) + data->dirY * cos(rSpeed);
		double oldPlaneX = data->planeX;
		data->planeX = data->planeX * cos(rSpeed) - data->planeY * sin(rSpeed);
		data->planeY = oldPlaneX * sin(rSpeed) + data->planeY * cos(rSpeed);
	}
	render_image(data);
}

int rgb_to_int(double r, double g, double b)
{
	int color = 0;
	color |= (int)(b * 255);
	color |= (int)(g * 255) << 8;
	color |= (int)(r * 255) << 16;
	return (color);
}
