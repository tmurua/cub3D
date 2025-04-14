/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:47:53 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/14 12:32:30 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#include "../../include/cubthreed.h"

int	input_validation(int argc, char **argv, t_game *game)
{
	if (argc != 2)
		return (print_err("Usage: ./cub3D <map_file.cub>"));
	if (parse_cub_file(game, argv[1]) == -1)
	{
		clean_game(game);
		return (-1);
	}
	if (init_game(game) == -1)
	{
		clean_game(game);
		return (-1);
	}
	return (1);
}
