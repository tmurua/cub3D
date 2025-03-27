/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:52:03 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/27 15:40:57 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	clean_game(t_game *game)
{
	int	i;

	if (game->texture.no)
		free(game->texture.no);
	if (game->texture.so)
		free(game->texture.so);
	if (game->texture.we)
		free(game->texture.we);
	if (game->texture.ea)
		free(game->texture.ea);
	if (game->mapdata.map)
	{
		i = 0;
		while (game->mapdata.map[i])
		{
			free(game->mapdata.map[i]);
			i++;
		}
		free(game->mapdata.map);
	}
}
