/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:47:53 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/21 07:29:00 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	input_validation(int argc, char **argv, t_game *game)
{
	if (argc != 2)
		return (print_err("Usage: ./cub3D <map_file.cub>"));
	if (!parse_map(game, argv[1]))
		return (print_err("Error parsing scene file"));
	if (!init_game(game))
		return (print_err("Error initializing game"));
	(void)game;
	return (1);
}

int	init_game(t_game *game)
{
	// implement miniLibX window initialization, texture loading, player state...
	(void)game;
	return (1);
}
