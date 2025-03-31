#include "raycaster.h"

int	handle_input(t_data *data)
{
	if (data->move[0]) // Up)
		move(data, 1);
	if (data->move[1]) // Down)
		move(data, -1);
	if (data->move[3]) // a)
		strafe(data, -1);
	if (data->move[2]) // d)
		strafe(data, 1);
	if (data->move[5]) // Left)
		pivot(data, 1);
	if (data->move[4]) // Right)
		pivot(data, -1);
	return (0);
}

void move(t_data *data, int dir)
{
	double mSpeed;

	mSpeed = data->frameTime * 5.0;
	if(data->map[(int)(data->posY + data->dirY * mSpeed * dir)][(int)data->posX] == 0)
		data->posY += data->dirY * mSpeed * dir;
	if(data->map[(int)data->posY][(int)(data->posX + data->dirX * mSpeed * dir)] == 0)
		data->posX += data->dirX * mSpeed * dir;
}

void strafe(t_data *data, int dir)
{
	double mSpeed;

	mSpeed = data->frameTime * 5.0;
	if(data->map[(int)(data->posX + data->planeX * mSpeed * dir)][(int)data->posY] == 0)
		data->posX += data->planeX * mSpeed * dir;
	if(data->map[(int)data->posX][(int)(data->posY + data->planeY * mSpeed * dir)] == 0)
		data->posY += data->planeY * mSpeed * dir;
}

void pivot(t_data *data, int pivot)
{
	double rSpeed;
	double oldDirX;
	double oldPlaneX;

	rSpeed = data->frameTime * 3.0 * pivot;
	oldDirX = data->dirX;
	data->dirX = data->dirX * cos(rSpeed) - data->dirY * sin(rSpeed);
	data->dirY = oldDirX * sin(rSpeed) + data->dirY * cos(rSpeed);
	oldPlaneX = data->planeX;
	data->planeX = data->planeX * cos(rSpeed) - data->planeY * sin(rSpeed);
	data->planeY = oldPlaneX * sin(rSpeed) + data->planeY * cos(rSpeed);
}
