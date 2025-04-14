/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubthreed.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:30:34 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/14 12:03:54 by tmurua           ###   ########.fr       */
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
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

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

typedef struct s_data
{
	int			*map;
	int			map_rows;
	int			map_cols;
	int			x;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	long long	time;
	long long	old_time;
	double		frame_time;
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			x_step;
	int			end;
	int			ll;
	int			**texture[4];
	int			tex;
	int			tex_x;
	int			move[6];
	int			side;
	double		ray_dir_x;
	double		ray_dir_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
	int			radio_car;
	int			mouse_x;
	double		mouse_offset;
	double		screen_center;
	double		player_angle;
	double		running_speed;
	t_game		g;
}				t_data;

// utils.c
long long		now(void);
int				initialize_img(t_data *d);
int				destroy(t_data *d);

// movement.c
int				handle_input(t_data *d);
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
void			draw_walls(t_data *d);
void			calc_step_and_sidedist(t_data *d);
void			draw_sky_and_floor(t_data *d);
void			render_image(t_data *d);
int				render_image_wrapper(void *param);

// radiocar.c
int				handle_mouse_scroll(int button, int x, int y, t_data *d);
int				steer_car(t_data *d);
void			update_player_position(t_data *d);
void			update_player_direction(t_data *d);

/* init/init_game.c */
int				init_game(t_game *game);
int				initialize_data(t_data *d, t_game *game);
void			copy_colors(t_data *d, t_game *game);

/* init/init_player.c */
int				set_initial_orientation(t_data *d, char orientation);
void			set_north(t_data *d);
void			set_south(t_data *d);
void			set_east(t_data *d);
void			set_west(t_data *d);

/* init/init_map.c */
void			load_parsed_map(t_data *d, t_game *game);
int				*convert_parsed_map(t_game *game);
int				convert_map_cell(char c);
int				get_map_index(t_data *d, int x, int y);

#endif
