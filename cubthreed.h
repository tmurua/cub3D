/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubthreed.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsternbe <tsternbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:30:34 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/04 13:04:18 by tsternbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBTHREED_H
# define CUBTHREED_H
# define SCREENWIDTH 1400
# define SCREENHEIGHT 700
# define TEXWIDTH 64
# define TEXHEIGHT 64
# include "cub3D.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

// this struct loads a texture from an xmp file, then writes the pixels over to
// d->texture. After each texture has been written during initialization, the img
// is destroyed
typedef struct s_image
{
	void		*ptr;
	char		*addr;
	int			h;
	int			w;
	int			bpp;
	int			end;
	int			ll;
}				t_image;

// Data struct that holds all vars necessary to loop and render the game.
// !! The first 8 are read from the file via the parser.
// The rest are initialized or calculated by raycaster
typedef struct s_data
{
	int			map_width;		// !!NEW VAR. From parser
	int			map_height;		// !!NEW VAR. From parser
	int 		**map;			// !!array storing map. NEEDS TO BE ALLOCATED. THEN PARSER
	int			**texture[4];	// !!array of double pointers saving the four textures. Save texture 1-4 here.
	int			floor;			// !! NEW VAR. From parser. Floor color
	int			ceiling;		// !! NEW VAR. From parser. Ceiling color
	double		pos_x;			// !!exact x position of player. ex pos_x == 3.724 map_x == 3
	double		pos_y;			// !!exact y position of player
	double		dir_x;			// !!direction in x plane. -1 to 1. -1 is right
	double		dir_y;			// !!direction in y plane. -1 to 1. -1 is up.
	int			tex;			// current texture, see above
	int			map_x;			// x map grid position of player
	int			map_y;			// y map grid position of player
	double		plane_x;		// plane perpendicular to dir_x. Take formula from function pivot
	double		plane_y;		// plane perpendicular to dir_y. Take formula from function pivot
	int			x;				// which x column of the screen are we raycasting right now?
	long long	time;			// timestamp this rendering
	long long	old_time;		// timestamp last rendering
	double		frame_time;		// time passed between old_time and time == how long is the current frame?
	void		*mlx;			// mlx init ptr
	void		*win;			// mlx window ptr
	void		*img;			// mlx image ptr, for rendering the screen
	char		*addr;			// mlx img buffer array
	int			bpp;			// bits per pixel
	int			x_step;			// how many bits does the mlx image buffer step per pixel. Precalculated to save rendering speed
	int			end;			// endian
	int			ll;				// line length
	int			tex_x;			// x col of texture being used
	int			move[6];		// array saving the status of control commands(forwards, backwards, strafe r, strafe l, trun r, turn l). Pressed(1) or not pressed(0)
	int			side;			// did ray hit vertical or horizontal wall?
	double		ray_dir_x;		// x direction of the ray we are currently casting
	double		ray_dir_y;		// y direction of the ray we are currently casting
	double		delta_dist_x;	// FOR DDA
	double		delta_dist_y;	//	#
	double		side_dist_x;	//	#
	double		side_dist_y;	//	#
	int			step_x;			//	#
	int			step_y;			//	#
	int			radio_car;		// switch: radiocar mode. 1 == on, 0 == off
	int			mouse_x;		// x position in game window of mouse pointer
	double		mouse_offset;	// how far from the center the mouse pointer is, in relative scale from -1 to 1 where 0 is center
	double		screen_center;	// which x is center of screen. Calculated once and used in every loop
	double		player_angle;	// DELETE not used anymore
	double		running_speed;	// speed in radio car mode
}				t_data;

// utils.c
long long		now(void);
int				initialize_img(t_data *d);
int				destroy(t_data *d);

// movement.c
void			handle_input(t_data *d);
void			move(t_data *d, int dir);
void			strafe(t_data *d, int dir);
void			pivot(t_data *d, int pivot);

// hooks.c
int				handle_keypress(int keycode, t_data *d);
int				handle_keyrelease(int keycode, t_data *d);

// textures.c
void			free_texture(int **tex, int y);
int				**allocate_texture(int width, int height);
void			allocate_all_textures(t_data *d, int tex_width, int tex_height);
void			load_texture(t_data *d, int index, char *file);
void			textures(t_data *d, t_game *game);

// raycaster.c
int				which_texture(int side, int step_y, int step_x);
int				tex_x(t_data *d, double perp_wall_d);
void			tex_column_to_img(t_data *d, int line_h, int draw_start,
					int draw_end);
void			calc_tex_column(t_data *d);
void			digital_differential_analyzer(t_data *d);

// rendering.c
int				render_image_wrapper(void *param);
void			render_image(t_data *d);
void			draw_floor_and_ceiling(t_data *d);
void			draw_walls(t_data *d);
void			calc_step_and_sidedist(t_data *d);




// radiocar.c
int				handle_mouse_scroll(int button, int x, int y, t_data *d);
int				steer_car(t_data *d);

/* init/init_game.c */
int				init_game(t_game *game);
int				initialize_data(t_data *d, t_game *game);
//void			copy_colors(t_data *d, t_game *game);
int				load_parsed_map(t_data *d, t_game *g);
int**			allocate_map(t_data *d);

/* init/init_player.c */
int				set_initial_orientation(t_data *d, char orientation);
void			set_north(t_data *d);
void			set_south(t_data *d);
void			set_east(t_data *d);
void			set_west(t_data *d);

#endif
