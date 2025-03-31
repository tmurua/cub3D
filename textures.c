#include "raycaster.h"

void free_texture(int **tex, int y)
{
	int i;

	i = 0;
	while (i < y)
	{
		free(tex[i]);
		i++;
	}
}

int **allocate_texture(int width, int height)
{
	printf("entered allocate_textures/n");
	int	i;

	int **array = malloc(height * sizeof(int *));
	if (!array)
		return(NULL);
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

void allocate_all_textures(t_data *data, int tex_width, int tex_height)
{
	printf("entered allocate_all_textures/n");
	int	i;

	i = 0;
	while (i < 4)
	{
		data->texture[i] = allocate_texture(tex_width, tex_height);
		if (!data->texture[i])
		{
			perror("Failed to allocate texture");
			exit(1);
		}
		i++;
	}
}

void load_texture(t_data *data, int index, char *file)
{
	printf("entered load_textures/n");
	int		x;
	int		y;
	int		pixel_index;
	t_img	img;

	img.ptr = mlx_xpm_file_to_image(data->mlx, file, &img.w, &img.h);
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
			data->texture[index][y][x] = *(int *)(img.addr + pixel_index);
			x++;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, img.ptr);
}

void textures(t_data *data)
{
	printf("entered textures/n");
	allocate_all_textures(data, 64, 64);
	load_texture(data, 0, "textures/greystone.xpm");
	load_texture(data, 1, "textures/mossy.xpm");
	load_texture(data, 2, "textures/purplestone.xpm");
	load_texture(data, 3, "textures/redbrick.xpm");
}
