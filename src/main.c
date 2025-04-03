/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:07:15 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/03 20:26:01 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/* will take a *.cub file as parameter and init game to 0 */
int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (input_validation(argc, argv, &game) == -1)
		return (-1);
	clean_game(&game);
	printf("LAST: Floor: %d, Ceiling: %d\n", game.color.floor, game.color.ceiling);
	return (0);
}
