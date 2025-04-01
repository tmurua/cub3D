#include "raycaster.h"

void save_map(t_data *data)
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
            data->map[x][y] = worldMap[x][y];
        }
    }
}

void draw_walls(t_data *data)
{
	data->x = 0;
	while(data->x < screenWidth)
	{
		double cameraX = 2 * data->x / (double)screenWidth - 1;
		double rayDirX = data->dirX + data->planeX * cameraX;
		double rayDirY = data->dirY + data->planeY * cameraX;
//which box of the map we're in
		int mapX = (int)data->posX;
		int mapY = (int)data->posY;
//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
//length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);
		double perpWallDist;
//what direction to step in, x or y direction (either +1 or -1)
		int stepX;
		int stepY;
		int hit = 0; // was there a wall collision?
		int side; // was a NS or EW wall hit?
// calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;
		}
// peform DDA
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (data->map[mapX][mapY] > 0)
				hit = 1;
		}
// calculate distance projectes on camera direction
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
// calculate height of line to draw on screen
		int lineHeight = (int)(screenHeight / perpWallDist);
// calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;
//texturing calculations
		int tex;
		if (side == 1)
		{
			if (stepY > 0)
				tex = 0;
			else
				tex = 1;
		}
		else
		{
			if (stepX > 0)
				tex = 2;
			else
				tex = 3;
		}
//calculate value of wallX
		double	wallX;	//exactly where on the wall the ray hit
		if (side == 0)
			wallX = data->posX + perpWallDist * rayDirY;
		else
			wallX = data->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);
//x coordinate on the texture
		int	texX;
		texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;
// how much to increase the texture coordinate per screen pixel
		double step;
		step = 1.0 * texHeight / lineHeight;
//starting texture coordinate
		double	texPos;
		texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;
		int y;
		int texY;
		int	pixelPos;
		y = drawStart;
		while (y < drawEnd)
		{
			texY = (int)texPos & (texHeight - 1);
			texPos += step;
			pixelPos = y * data->ll + data->x * data->x_step;
			*(int *)(data->addr + pixelPos) = data->texture[tex][texY][texX];
			y++;
		}
		data->x++;
	}
}

/* void draw_walls(t_data *data)
{
	data->x = 0;
	while(data->x < screenWidth)
	{
		data->cameraX = 2 * data->x / (double)screenWidth - 1;
		data->rayDirX = data->dirX + data->planeX * data->cameraX;
		data->rayDirY = data->dirY + data->planeY * data->cameraX;
//which box of the map we're in
		data->mapX = (int)data->posX;
		data->mapY = (int)data->posY;
//length of ray from one x or y-side to next x or y-side
		data->deltaDistX = (data->rayDirX == 0) ? 1e30 : fabs(1.0 / data->rayDirX);
		data->deltaDistY = (data->rayDirY == 0) ? 1e30 : fabs(1.0 / data->rayDirY);
//what direction to step in, x or y direction (either +1 or -1)
// calculate step and initial sideDist
		if (data->rayDirX < 0)
		{
			data->stepX = -1;
			data->sideDistX = (data->posX - data->mapX) * data->deltaDistX;
		}
		else
		{
			data->stepX = 1;
			data->sideDistX = (data->mapX + 1.0 - data->posX) * data->deltaDistX;
		}
		if (data->rayDirY < 0)
		{
			data->stepY = -1;
			data->sideDistY = (data->posY - data->mapY) * data->deltaDistY;
		}
		else
		{
			data->stepY = 1;
			data->sideDistY = (data->mapY + 1.0 - data->posY) * data->deltaDistY;
		}
// peform DDA
		while (data->hit == 0)
		{
			if (data->sideDistX < data->sideDistY)
			{
				data->sideDistX += data->deltaDistX;
				data->mapX += data->stepX;
				data->side = 0;
			}
			else
			{
				data->sideDistY += data->deltaDistY;
				data->mapY += data->stepY;
				data->side = 1;
			}
			if (data->map[data->mapX][data->mapY] > 0)
				data->hit = 1;
		}
// calculate distance projectes on camera direction
		if (data->side == 0)
			data->perpWallDist = (data->sideDistX - data->deltaDistX);
		else
			data->perpWallDist = (data->sideDistY - data->deltaDistY);
// calculate height of line to draw on screen
		data->lineHeight = (int)(screenHeight / data->perpWallDist);
// calculate lowest and highest pixel to fill in current stripe
		data->drawStart = -data->lineHeight / 2 + screenHeight / 2;
		if (data->drawStart < 0)
			data->drawStart = 0;
		data->drawEnd = data->lineHeight / 2 + screenHeight / 2;
		if (data->drawEnd >= screenHeight)
			data->drawEnd = screenHeight - 1;
//texturing calculations
		if (data->side == 1)
		{
			if (data->stepY > 0)
				data->tex = 0;
			else
				data->tex = 1;
		}
		else
		{
			if (data->stepX > 0)
				data->tex = 2;
			else
				data->tex = 3;
		}
//calculate value of wallX
		if (data->side == 0)
			data->wallX = data->posX + data->perpWallDist * data->rayDirY;
		else
			data->wallX = data->posX + data->perpWallDist * data->rayDirX;
		data->wallX -= floor(data->wallX);
//x coordinate on the texture
		data->texX = (int)(data->wallX * (double)texWidth);
		if (data->side == 0 && data->rayDirX > 0)
			data->texX = texWidth - data->texX - 1;
		if (data->side == 1 && data->rayDirY < 0)
			data->texX = texWidth - data->texX - 1;
// how much to increase the texture coordinate per screen pixel
		data->step = 1.0 * texHeight / data->lineHeight;
//starting texture coordinate
		data->texPos = (data->drawStart - screenHeight / 2 + data->lineHeight / 2) * data->step;
		data->y = data->drawStart;
		while (data->y < data->drawEnd)
		{
			data->texY = (int)data->texPos & (texHeight - 1);
			data->texPos += data->step;
			data->pixelPos = data->y * data->ll + data->x * data->x_step;
			*(int *)(data->addr + data->pixelPos) = data->texture[data->tex][data->texY][data->texX];
			data->y++;
		}
		data->x++;
	}
} */

void draw_sky_and_floor(t_data *data)
{
	int y;
	int x;
	int	color;
	int	pixelPos;

	y = 0;
	while (y < screenHeight)
	{
		color = (y < screenHeight / 2) ? SKY : FLOOR;
		x = 0;
		while (x < screenWidth)
		{
			pixelPos = y * data->ll + x * data->x_step;
			*(int *)(data->addr + pixelPos) = color;
			x++;
		}
		y++;
	}
}
void render_image(t_data *data)
{
	data->time = now();
	data->frameTime = (data->time - data->oldTime) / 1000000.0;
	if (data->frameTime > 0.01667)
		data->frameTime = 0.01667;
	handle_input(data);
	draw_sky_and_floor(data);
	draw_walls(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	data->oldTime = data->time;
}

int	render_image_wrapper(void *param)
{
	render_image((t_data *)param);
	return (0);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		destroy(data);
	if (keycode == XK_a)
		data->move[3] = 1;
	if (keycode == XK_s || keycode == XK_Down)
		data->move[1] = 1;
	if (keycode == XK_d)
		data->move[2] = 1;
	if (keycode == XK_w || keycode == XK_Up)
		data->move[0] = 1;
	if (keycode == XK_Right)
		data->move[4] = 1;
	if (keycode == XK_Left)
		data->move[5] = 1;
	return(0);
}

int	handle_keyrelease(int keycode, t_data *data)
{
	if (keycode == XK_a)
		data->move[3] = 0;
	if (keycode == XK_s || keycode == XK_Down)
		data->move[1] = 0;
	if (keycode == XK_d)
		data->move[2] = 0;
	if (keycode == XK_w || keycode == XK_Up)
		data->move[0] = 0;
	if (keycode == XK_Right)
		data->move[4] = 0;
	if (keycode == XK_Left)
		data->move[5] = 0;
	return(0);
}

int	main()
{
	t_data	data;

	if (initialize_data(&data) != 0)
		return (1);
//	initialize_calc(&data);
	save_map(&data);
	textures(&data);

	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, &destroy, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_loop_hook(data.mlx, &render_image_wrapper, &data);
	mlx_loop(data.mlx);
}
