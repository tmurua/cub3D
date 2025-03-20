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

void render_image(t_data *data)
{
	data->rayX = 0;
	while(data->rayX < screenWidth)
	{
		double cameraX = 2 * data->rayX / (double)screenWidth - 1;
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
// choose wall color
		int color;
		if (side == 1 && data->dirY > 0)
			color = SOUTH;
		else if (side == 1 && data->dirY < 0)
			color = NORTH;
		else if (side == 0 && data->dirX > 0)
			color = EAST;
		else if (side == 0 && data->dirX < 0)
			color = WEST;
		if (data->bpp != 32)
			color = mlx_get_color_value(data->mlx, color);
		if (data->end == 1)
			endian_Line(data, drawStart, drawEnd, color);
		else
			non_Endian_Line(data, drawStart, drawEnd, color);
		data->rayX++;
	}
	data->oldTime = data->time;
	data->time = now();
	data->frameTime = (data->time - data->oldTime) / 1000000.0;
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void endian_Line(t_data *data, int drawStart, int drawEnd, int color)
{
	int y;
	int	pixel;
	int	paint;

	y = 0;

	while (y < screenHeight)
	{
		pixel = (y * data->ll) + (data->rayX * 4);
		if (y < drawStart)
			paint = SKY;
		else if (y < drawEnd)
			paint = color;
		else
			paint = FLOOR;
		data->addr[pixel] = (paint >> 24);
		data->addr[pixel + 1] = (paint >> 16) & 0xFF;
		data->addr[pixel + 2] = (paint >> 8) & 0xFF;
		data->addr[pixel + 3] = (paint) & 0xFF;
		y++;
	}
}

void non_Endian_Line(t_data *data, int drawStart, int drawEnd, int color)
{
	int y;
	int	pixel;
	int	paint;

	y = 0;

	while (y < screenHeight)
	{
		pixel = (y * data->ll) + (data->rayX * 4);
		if (y < drawStart)
			paint = SKY;
		else if (y < drawEnd)
			paint = color;
		else
			paint = FLOOR;
		data->addr[pixel] = (paint) & 0xFF;
		data->addr[pixel + 1] = (paint >> 8) & 0xFF;
		data->addr[pixel + 2] = (paint >> 16) & 0xFF;
		data->addr[pixel + 3] = (paint >> 24);
		y++;
	}
}

int	main()
{
	t_data	data;

	if (initialize(&data) != 0)
		return (1);
	save_map(&data);
	render_image(&data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, &destroy, &data);
	mlx_loop(data.mlx);
}
