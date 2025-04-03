/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:08:51 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/03 15:29:30 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* libraries */
# include "../libft/libft.h"
/* read(), write(), and close() */
# include <unistd.h>
/* open() */
# include <fcntl.h>
/* printf() and perror() */
# include <stdio.h>
/* malloc(), free(), and exit() */
# include <stdlib.h>
/* gettimeofday() */
# include <sys/time.h>
/* functions of the math library (-lm man man 3 math) */
# include <math.h>
/* functions of the MinilibX library */
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

/* macros */
/* buffer for get_next_line */
# define BUFFER_SIZE 20
/* set of allowed chars in game->map.lines */
# define ALLOWED_MAP_CHARS " 01NSEW"

/* stuctures */
/* texture file paths for each wall direction */
typedef struct s_texture
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
}				t_texture;

/* color values (in 0xRRGGBB format) for floor and ceiling */
typedef struct s_color
{
	int			floor;
	int			ceiling;
}				t_color;

/*	array of strings with each row (line) of the map in the cub file,
	nbr or rows and cols, and flag to check if map started on cub file */
typedef struct s_map
{
	char		**lines;
	int			rows;
	int			cols;
	int			map_started;
}				t_map;

/* header flags indicating if each header has been parsed to prevent duplic */
typedef struct s_header
{
	int			no;
	int			so;
	int			we;
	int			ea;
	int			f;
	int			c;
}				t_header;

/* player's starting position and orientation */
typedef struct s_player
{
	double		x;
	double		y;
	char		orientation;
}				t_player;

/* main game structure containing all modules */
typedef struct s_game
{
	t_texture	texture;
	t_color		color;
	t_map		map;
	t_header	header;
	t_player	player;
}				t_game;

/* function prototypes */
/* input/input_handler.c */
int				input_validation(int argc, char **argv, t_game *game);

/* error/error_utils.c */
int				print_err(char *str_err);
void			malloc_error(void);
int				free_and_return(char *ptr, int ret);

/* parser/parse_cub_file.c */
int				parse_cub_file(t_game *game, char *filename);
int				open_cub_file(char *filename);
int				has_cub_extension(char *filename);
int				handle_lines_loop(int fd, t_game *game, int *found_non_empty);
int				process_single_file_line(char *line, t_game *game,
					int *found_non_empty);

/* parser/process_line c */
int				check_line_type(char *input_line, t_game *game);
int				is_header_line(char *line);
int				parse_header_line(char *line, t_game *game);
int				process_map_line(char *line, t_game *game);

/* parser/get_next_line.c */
char			*get_next_line(int fd, char **leftover);
char			*read_until_newline(int fd, char *init_str);
char			*append_until_newline(int fd, char *line);
char			*process_leftover(char *line, char **leftover);

/* parser/parse_texture.c */
int				handle_texture_hdr(char *line, char **texture_field,
					int *header_flag);
int				parse_texture_line(char *line, char **texture_out);
int				check_if_file_exists(char *texture_file_path);
int				has_xpm_extension(char *texture_file_path);

/* parser/parse_color.c */
int				handle_color_hdr(char *line, int *color_field,
					int *header_flag);
int				parse_color_line(char *line, int *color_out);
int				validate_color_tokens(char **tokens, int *red, int *green,
					int *blue);
void			ft_free_strs(char **strs);

/* parser/validate_map_requirements.c */
int				validate_map_requirements(t_game *game);
int				validate_allowed_chars(t_game *game);
int				is_allowed_map_char(char current_char);
int				validate_player_position(t_game *game);
int				process_player_in_cell(t_game *game, int x, int y, int *found);

/* parser/flood_fill_algorithm.c */
int				perform_flood_fill(t_game *game);
int				flood_fill_on_copy(char **map_lines_copy, int rows, int cols,
					t_map *start);
int				flood_fill(t_game *game, int r, int c);

/* parser/map_padding.c */
char			**copy_padded_map_lines(t_game *game, int *total_cols);
int				get_max_row_length(t_game *game);
char			*pad_row(char *row, int max_row_length);
void			fill_padded_row(char *padded, char *trim, int max_row_length);
void			free_map_lines_copy(char **map_lines_copy, int map_rows);

/* game/game_cleanup.c */
void			clean_game(t_game *game);

#endif
