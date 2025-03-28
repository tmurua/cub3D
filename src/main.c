/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:07:15 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/24 16:34:17 by tmurua           ###   ########.fr       */
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

	// main_loop(&game);
	clean_game(&game);
	return (0);
}
