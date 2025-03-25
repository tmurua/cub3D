/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:08:51 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/25 19:54:29 by tmurua           ###   ########.fr       */
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
/* main structure that can be passed as a parameter containing relevant data */
typedef struct s_game
{
	/* Texture paths */
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	/* Colors stored as 0xRRGGBB */
	int		floor_color;
	int		ceiling_color;
	/* Map: an array of strings */
	char	**map;
	int		map_rows;
	/* other game-related fields can be added here */
	int		hdr_no;
	int		hdr_so;
	int		hdr_we;
	int		hdr_ea;
	int		hdr_f;
	int		hdr_c;
}			t_game;

/* function prototypes */
/* input/input_handler.c */
int			input_validation(int argc, char **argv, t_game *game);
int			init_game(t_game *game);

/* error/error_utils.c */
int			print_err(char *str_err);
void		malloc_error(void);
int			free_and_return(char *ptr, int ret);

/* parser/parse_cub_file.c */
int			parse_cub_file(t_game *game, char *filename);
int			process_file_lines(int fd, t_game *game, int *found_non_empty);
int			open_cub_file(char *filename);
int			has_cub_extension(char *filename);

/* parser/process_line c */
int			process_line(char *input_line, t_game *game);
int			is_header_line(char *line);
int			process_map_line(char *line, t_game *game);
void		ft_free_strs(char **strs);

/* parser/get_next_line.c */
char		*get_next_line(int fd);
char		*read_concatenate_line(int fd, char *left_c, char *buffer);
char		*set_leftover_chars(char *current_line);

/* parser/parse_header.c */
int			parse_header_line(char *line, t_game *game);
int			parse_color_line(char *line, int *color_out);
int			validate_color_tokens(char **tokens, int *red, int *green,
				int *blue);
int			parse_texture_line(char *line, char **texture_out);
int			has_xpm_extension(char *filename);

/* parser/parser_utils.c */
int			handle_texture_header(char *dup_msg, char *line, int *hdr_flag,
				char **texture_field);
int			handle_color_header(char *dup_msg, char *line, int *hdr_flag,
				int *color_field);

/* parser/parse_map.c */
int			validate_map_layout(t_game *game);
int			validate_all_borders(t_game *game);
int			validate_row_borders(char *row);
int			validate_allowed_chars(t_game *game);
int			is_allowed_map_char(char c);

/* game/game_cleanup.c */
void		clean_game(t_game *game);

#endif
