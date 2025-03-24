/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:47:53 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/24 11:35:11 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	input_validation(int argc, char **argv, t_game *game)
{
	if (argc != 2)
		return (print_err("Usage: ./cub3D <map_file.cub>"));
	if (parse_map(game, argv[1]) == -1)
		return (-1);
	if (init_game(game) == -1)
		return (-1);
	(void)game;
	return (1);
}

int	init_game(t_game *game)
{
	// implement miniLibX window initialization, texture loading, player state...
	(void)game;
	return (1);
}
