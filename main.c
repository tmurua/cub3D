/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:07:15 by tmurua            #+#    #+#             */
/*   Updated: 2025/03/22 10:09:59 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* will take a *.cub file, a map, as a parameter */
int	main(int argc, char **argv)
{
	t_game	game;

	if (input_validation(argc, argv, &game) == -1)
		return (-1);

	// main_loop(&game);
	// clean_game(&game);
	return (0);
}
