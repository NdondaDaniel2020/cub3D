/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_player_texture_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:29:02 by nmatondo          #+#    #+#             */
/*   Updated: 2025/03/28 19:37:39 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static int	load_player_texture_util(void *mlx, t_data *img, t_3d dim)
{
	(void)mlx;
	printf("%s\n", img->player_texture_paths[dim.m][dim.l][dim.c]);
	// img->player_texture[dim.m][dim.l][dim.c] = mlx_xpm_file_to_image(mlx,
	// 	img->player_texture_paths[dim.m][dim.l][dim.c],
	// 	&img->player_texture_width[dim.m][dim.l][dim.c],
	// 	&img->player_texture_height[dim.m][dim.l][dim.c]
	// );
	// if (!img->player_texture[dim.m][dim.l][dim.c])
    // {
    //     printf("Error loading texture\n");
    //     return (1);
    // }
	// img->player_texture_addr[dim.m][dim.l][dim.c] = mlx_get_data_addr(
	// 	img->player_texture[dim.m][dim.l][dim.c],
	// 	&img->player_texture_bits_per_pixel[dim.m][dim.l][dim.c],
	// 	&img->player_texture_line_length[dim.m][dim.l][dim.c],
	// 	&img->player_texture_endian[dim.m][dim.l][dim.c]);
	return (0);
}

static t_texture_paths	*path_player_images(void)
{
	int						l;
	int						c;
	static t_texture_paths	paths;

	l = 0;
	while (l < 3)
	{
		c = 0;
		while (c < 14)
		{
			paths[0][l][c] = ((char *(*)[3][14])escopeta())[0][l][c];
			paths[1][l][c] = ((char *(*)[3][14])lupara())[0][l][c];
			paths[2][l][c] = ((char *(*)[3][14])mgun())[0][l][c];
			paths[3][l][c] = ((char *(*)[3][14])escopeta_dupla())[0][l][c];
			paths[4][l][c] = ((char *(*)[3][14])pistola())[0][l][c];
			c++;
		}
		l++;
	}
	return (&paths);
}

static void	set_path_of_player_images(t_data *img)
{
	t_3d			dim;
	t_texture_paths	*player_texture_paths;

	dim.m = 0;
	player_texture_paths = path_player_images();
	while (dim.m < WEAPON_TYPES)
	{
		dim.l = 0;
		while (dim.l < ACTION_TYPES)
		{
			dim.c = 0;
			while (dim.c < IMAGE_COUNT)
			{
				img->player_texture_paths[dim.m][dim.l]
					[dim.c] = (*player_texture_paths)[dim.m][dim.l][dim.c];
				dim.c++;
			}
			dim.l++;
		}
		dim.m++;
	}
}

static int	get_image_quantity(int index)
{
	if (index == 0)
		return (13);
	if (index == 1)
		return (5);
	if (index == 2 || index == 4)
		return (6);
	if (index == 3)
		return (12);
	return (6);
}

int	load_player_texture(void *mlx, t_data *img)
{
	int		len;
	t_3d	dim;

	dim.m = 0;
	set_path_of_player_images(img);
	while (dim.m < 5)
	{
		dim.l = 0;
		len = get_image_quantity(dim.m);
		while (dim.l < 3)
		{
			dim.c = 0;
			while (dim.c < len)
			{
				 if (load_player_texture_util(mlx, img, dim))
					return (1);
				dim.c++;
			}
			dim.l++;
		}
		dim.m++;
	}
	return (0);
}
