/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsternbe <tsternbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:47:53 by tmurua            #+#    #+#             */
/*   Updated: 2025/04/04 11:38:59 by tsternbe         ###   ########.fr       */
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
		printf("Failed parse_cub_file\n");
		clean_game(game);
		return (-1);
	}
	if (init_game(game) == -1)
	{
		printf("Failed init_game\n");
		clean_game(game);
		return (-1);
	}
//	(void)game;
	return (1);
}
