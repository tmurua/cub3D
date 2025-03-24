/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:08:51 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/24 11:51:17 by tmurua           ###   ########.fr       */
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
}	t_game;

/* function prototypes */
/* input/input_handler.c */
int		input_validation(int argc, char **argv, t_game *game);
int		init_game(t_game *game);

/* error/error_utils.c */
int		print_err(char *str_err);
void	malloc_error(void);
int		free_and_return(char *ptr, int ret);

/* parser/parse_map.c */
int		parse_map(t_game *game, char *filename);
int		open_cub_file(char *filename);
int		has_cub_extension(char *filename);

/* parser/process_line c */
int		process_line(char *input_line, t_game *game);
int		is_header_line(char *line);
int		process_header_line(char *line, t_game *game);
int		process_map_line(char *line, t_game *game);
void	ft_free_strs(char **strs);

/* parser/get_next_line.c */
char	*get_next_line(int fd);
char	*read_concatenate_line(int fd, char *left_c, char *buffer);
char	*set_leftover_chars(char *current_line);

/* game/game_cleanup.c */
void	clean_game(t_game *game);

#endif
