/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:47:53 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/20 15:15:24 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	input_validation(int argc, char **argv, t_game *game)
{
	if (argc != 2)
	{
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (0);
	}
	if (!parse_map(game, argv[1]))
	{
		printf("Error parsing scene file.\n");
		return (0);
	}
	if (!init_game(game))
	{
		printf("Error initializing game.\n");
		return (0);
	}
	(void)game;
	return (1);
}

int	init_game(t_game *game)
{
	// implement miniLibX window initialization, texture loading, player state...
	(void)game;
	return (1);
}
