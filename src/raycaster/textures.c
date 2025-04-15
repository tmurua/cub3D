/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:14:50 by tsternbe          #+#    #+#             */
/*   Updated: 2025/04/15 14:41:55 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cubthreed.h"
#include "../../include/cub3D.h"

void	free_texture(int **texture, int y)
{
	int	i;

	i = 0;
	while (i < y)
	{
		free(texture[i]);
		i++;
	}
	free(texture);
}

int	**allocate_texture(int width, int height)
{
	int	i;
	int	**array;

	array = malloc(height * sizeof(int *));
	if (!array)
		return (NULL);
	i = 0;
	while (i < height)
	{
		array[i] = malloc(width * sizeof(int));
		if (!array[i])
		{
			while (--i >= 0)
				free(array[i]);
			free(array);
			return (NULL);
		}
		i++;
	}
	return (array);
}

void	allocate_all_textures(t_data *d, int tex_width, int tex_height)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		d->texture[i] = allocate_texture(tex_width, tex_height);
		if (!d->texture[i])
		{
			perror("Failed to allocate texture");
			exit(1);
		}
		i++;
	}
}

void	load_texture(t_data *d, int index, char *file)
{
	int		x;
	int		y;
	int		pixel_index;
	t_image	img;

	img.ptr = mlx_xpm_file_to_image(d->mlx, file, &img.w, &img.h);
	if (!img.ptr)
	{
		perror("Failed to load texture from file");
		exit(1);
	}
	img.addr = mlx_get_data_addr(img.ptr, &img.bpp, &img.ll, &img.end);
	y = 0;
	while (y < img.h)
	{
		x = 0;
		while (x < img.w)
		{
			pixel_index = y * img.ll + x * (img.bpp / 8);
			d->texture[index][y][x] = *(int *)(img.addr + pixel_index);
			x++;
		}
		y++;
	}
	mlx_destroy_image(d->mlx, img.ptr);
}

void	textures(t_data *d, t_game *game)
{
	allocate_all_textures(d, 64, 64);
	load_texture(d, 0, game->texture.no);
	load_texture(d, 1, game->texture.so);
	load_texture(d, 2, game->texture.we);
	load_texture(d, 3, game->texture.ea);
}
