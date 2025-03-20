#ifndef RAYCASTER_H
#define RAYCASTER_H
#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480
#define NORTH 65280
#define SOUTH 8388736
#define EAST 16744448
#define WEST 16711680
#define SKY	8421631
#define FLOOR 0
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stddef.h>
# include <math.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>

typedef struct s_data
{
	int 		map[mapWidth][mapHeight];
	int			rayX;
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	long long	time;
	long long	oldTime;
	double		frameTime;
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			end;
	int			ll;
}				t_data;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		h;
	int		w;
	int		bpp;
	int		end;
	int		ll;
}			t_img;

//raycaster.c
long long	now();
int			initialize(t_data *data);
int			handle_keypress(int keysym, t_data *data);
int			destroy(t_data *data);
void		attempt_move(t_data *data, int m_x, int m_y, int pivot);
int 		rgb_to_int(double r, double g, double b);

//main.c
void save_map(t_data *data);
void render_image(t_data *data);
void endian_Line(t_data *data, int drawStart, int drawEnd, int color);
void non_Endian_Line(t_data *data, int drawStart, int drawEnd, int color);

#endif
