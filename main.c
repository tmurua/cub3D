/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:07:15 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/22 15:59:14 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* will take a *.cub file, a map, as a parameter */
int	main(int argc, char **argv)
{
	t_game	game;

	game.map = NULL;
	game.map_rows = 0;
	if (input_validation(argc, argv, &game) == -1)
		return (-1);

	// main_loop(&game);
	clean_game(&game);
	return (0);
}

void	clean_game(t_game *game)
{
	int	i;

	if (game->no_texture)
		free(game->no_texture);
	if (game->so_texture)
		free(game->so_texture);
	if (game->we_texture)
		free(game->we_texture);
	if (game->ea_texture)
		free(game->ea_texture);
	if (game->map)
	{
		i = 0;
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
}
/* ft lines: 20 */
