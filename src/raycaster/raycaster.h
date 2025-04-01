#ifndef RAYCASTER_H
#define RAYCASTER_H
#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480
#define texWidth 64
#define texHeight 64
#define MINDIST 0.1;
#define	FORWARDS	0;
#define	BACKWARDS	1;
#define	RTRAFE		2;
#define	LSTRAFE		3;
#define	RPIVOT		4;
#define	LPIVOT		5;
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

typedef struct s_data
{
	int 		map[mapWidth][mapHeight];
	int			x;
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
	int			x_step;
	int			end;
	int			ll;
	int			**texture[4];
	int			move[6];
/*	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	double		sideDistX;
	double		sideDistY;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	int			tex;
	double		wallX;			//exactly where on the wall the ray hit
	int			texX;
	double		step;
	double		texPos;
	int			y;
	int			texY;
	int			pixelPos;*/
}				t_data;


//raycaster.c
long long	now();
int			initialize_data(t_data *data);
//void		initialize_calc(t_data *data);
int			destroy(t_data *data);
int 		rgb_to_int(double r, double g, double b);

//movement.c
int		handle_input(t_data *data);
void	move(t_data *data, int dir);
void	strafe(t_data *data, int dir);
void	pivot(t_data *data, int pivot);

//main.c
void save_map(t_data *data);
void draw_walls(t_data *data);
void draw_sky_and_floor(t_data *data);
void	render_image(t_data *data);
int	render_image_wrapper(void *param);
int	handle_keypress(int keycode, t_data *data);
int	handle_keyrelease(int keycode, t_data *data);

//textures.c
void free_texture(int **tex, int y);
int **allocate_texture(int width, int height);
void allocate_all_textures(t_data *data, int tex_width, int tex_height);
void load_texture(t_data *data, int index, char *file);
void textures(t_data *data);

#endif
