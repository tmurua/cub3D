/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:08:51 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/27 16:41:14 by tmurua           ###   ########.fr       */
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

/* an array of strings, its dimensions, and flag to check if map's started */
typedef struct s_mapdata
{
	char		**map;
	int			rows;
	int			cols;
	int			map_started;
}				t_mapdata;

/* header flags indicating if each header has been parsed */
typedef struct s_header
{
	int			hdr_no;
	int			hdr_so;
	int			hdr_we;
	int			hdr_ea;
	int			hdr_f;
	int			hdr_c;
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
	t_mapdata	mapdata;
	t_header	header;
	t_player	player;
}				t_game;

/* function prototypes */
/* input/input_handler.c */
int				input_validation(int argc, char **argv, t_game *game);
int				init_game(t_game *game);

/* error/error_utils.c */
int				print_err(char *str_err);
void			malloc_error(void);
int				free_and_return(char *ptr, int ret);

/* parser/parse_cub_file.c */
int				parse_cub_file(t_game *game, char *filename);
int				process_file_lines(int fd, t_game *game, int *found_non_empty);
int				process_single_file_line(char *line, t_game *game,
					int *found_non_empty);
int				open_cub_file(char *filename);
int				has_cub_extension(char *filename);

/* parser/process_line c */
int				process_line(char *input_line, t_game *game);
int				is_header_line(char *line);
int				process_map_line(char *line, t_game *game);

/* parser/get_next_line.c */
char			*get_next_line(int fd, char **leftover);
char			*read_until_newline(int fd, char *init_str);
char			*append_until_newline(int fd, char *line);
char			*process_leftover(char *line, char **leftover);

/* parser/parse_header.c */
int				parse_header_line(char *line, t_game *game);
int				parse_color_line(char *line, int *color_out);
int				validate_color_tokens(char **tokens, int *red, int *green,
					int *blue);
int				parse_texture_line(char *line, char **texture_out);
int				has_xpm_extension(char *filename);

/* parser/parser_utils.c */
int				handle_texture_header(char *dup_msg, char *line, int *hdr_flag,
					char **texture_field);
int				handle_color_header(char *dup_msg, char *line, int *hdr_flag,
					int *color_field);
void			ft_free_strs(char **strs);

/* parser/parse_map.c */
int				validate_map_layout(t_game *game);
int				validate_all_borders(t_game *game);
int				validate_row_borders(char *row);
int				validate_allowed_chars(t_game *game);
int				is_allowed_map_char(char c);

/* parser/validate_map.c */
int				validate_map_requirements(t_game *game);
int				validate_player_position(t_game *game);
int				process_player_in_cell(t_game *game, int row, int col,
					int *found);

/* parser/flood_fill_algorithm.c */
int				perform_flood_fill(t_game *game);
int				flood_fill_on_copy(char **map_copy, int rows, int cols,
					t_mapdata *start);
int				flood_fill(t_game *game, int r, int c);

/* parser/map_padding.c */
char			**copy_map_padded(t_game *game, int *cols);
int				get_max_trimmed_length(t_game *game);
char			*pad_row(char *row, int max_len);
void			fill_padded_row(char *padded, char *trim, int max_len);
void			free_map_copy(char **map_copy, int rows);

/* game/game_cleanup.c */
void			clean_game(t_game *game);

#endif
