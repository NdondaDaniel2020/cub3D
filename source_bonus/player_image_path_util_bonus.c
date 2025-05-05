/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_image_path_util_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:10:10 by nmatondo          #+#    #+#             */
/*   Updated: 2025/05/03 19:17:49 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	load_ceil_and_floor_texture(void *mlx, t_data *img)
{
	img->ceil_texture_paths = "textures/ceil/ceil.xpm";
	img->ceil_texture = mlx_xpm_file_to_image(mlx, img->ceil_texture_paths,
			&img->ceil_texture_width, &img->ceil_texture_height);
	if (!img->ceil_texture)
		return (msg_error_image_not_found(4, mlx, img), 1);
	img->ceil_texture_addr = mlx_get_data_addr(img->ceil_texture,
			&img->ceil_texture_bits_per_pixel, &img->ceil_texture_line_length,
			&img->ceil_texture_endian);
	img->floor_texture_paths = "textures/floor/floor0.xpm";
	img->floor_texture = mlx_xpm_file_to_image(mlx, img->floor_texture_paths,
			&img->floor_texture_width, &img->floor_texture_height);
	if (!img->floor_texture)
		return (msg_error_image_not_found(5, mlx, img), 1);
	img->floor_texture_addr = mlx_get_data_addr(img->floor_texture,
			&img->floor_texture_bits_per_pixel, &img->floor_texture_line_length,
			&img->floor_texture_endian);
	return (0);
}

t_preload	*set_preload_path(t_preload *preload)
{
	preload->logo[0].path = "textures/preload/odyssey/odyssey-1.xpm";
	preload->logo[1].path = "textures/preload/odyssey/odyssey-2.xpm";
	preload->logo[2].path = "textures/preload/odyssey/odyssey-3.xpm";
	preload->logo[3].path = "textures/preload/odyssey/odyssey-4.xpm";
	preload->logo[4].path = "textures/preload/odyssey/odyssey-5.xpm";
	preload->logo[5].path = "textures/preload/odyssey/odyssey-6.xpm";
	preload->logo[6].path = "textures/preload/odyssey/odyssey-7.xpm";
	preload->logo[7].path = "textures/preload/odyssey/odyssey-8.xpm";
	preload->logo[8].path = "textures/preload/odyssey/odyssey-9.xpm";
	preload->logo[9].path = "textures/preload/odyssey/odyssey-10.xpm";
	preload->logo[10].path = "textures/preload/odyssey/odyssey-11.xpm";
	preload->logo[11].path = "textures/preload/odyssey/odyssey-12.xpm";
	preload->logo[12].path = "textures/preload/odyssey/odyssey-13.xpm";
	preload->background.path = "textures/preload/background.xpm";
	return (preload);
}

int	set_preload_image(t_preload *preload, void *mlx)
{
	int	i;

	i = -1;
	preload->background.img = mlx_xpm_file_to_image(mlx,
			preload->background.path, &preload->background.width,
			&preload->background.height);
	if (!preload->background.img)
		return (14);
	preload->background.addr = mlx_get_data_addr(preload->background.img,
			&preload->background.bits_per_pixel,
			&preload->background.line_length, &preload->background.endian);
	while (++i < 13)
	{
		preload->logo[i].img = mlx_xpm_file_to_image(mlx, preload->logo[i].path,
				&preload->logo[i].width, &preload->logo[i].height);
	}
	while (--i >= 0)
	{
		if (!preload->logo[i].img)
			return (i + 1);
		preload->logo[i].addr = mlx_get_data_addr(preload->logo[i].img,
				&preload->logo[i].bits_per_pixel, &preload->logo[i].line_length,
				&preload->logo[i].endian);
	}
	return (0);
}

int	free_preload(t_preload *preload, void *mlx)
{
	int	start;

	start = 12;
	while (start >= 0)
	{
		if (preload->logo[start].img)
		{
			mlx_destroy_image(mlx, preload->logo[start].img);
			preload->logo[start].img = NULL;
		}
		--start;
	}
	if (preload->background.img)
	{
		mlx_destroy_image(mlx, preload->background.img);
		preload->background.img = NULL;
	}
	if (preload->img)
	{
		mlx_destroy_image(mlx, preload->img);
		preload->img = NULL;
	}
	return (0);
}

int	set_preload_default(t_preload *preload)
{
	int	i;

	i = 0;
	while (i < 13)
	{
		preload->logo[i].img = NULL;
		i++;
	}
	preload->img = NULL;
	preload->background.img = NULL;
	return (0);
}

int	init_preload(t_preload *preload, void *mlx)
{
	char	*str;
	char	*num;
	int		res;

	set_preload_default(preload);
	set_preload_path(preload);
	preload->img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!preload->img)
		return (free_preload(preload, mlx),
			printerror("Image preload cannot be created"), 1);
	preload->addr = mlx_get_data_addr(preload->img, &preload->bits_per_pixel,
			&preload->line_length, &preload->endian);
	res = set_preload_image(preload, mlx);
	if (!preload->background.img)
		return (free_preload(preload, mlx),
			printerror("Invalid texture preload background"), 1);
	if (res != 0)
	{
		num = ft_itoa(res);
		str = ft_strjoin("Invalid texture preload logo number: ", num);
		printerror(str);
		free_preload(preload, mlx);
		return (free(str), free(num), 1);
	}
	return (0);
}

int	load_all_texteres(void *mlx, t_data *img, t_master *master)
{
	return (init_preload(&master->preload, mlx)
		|| load_ceil_and_floor_texture(mlx, img) || load_textures(mlx, img,
			master) || load_player_texture(mlx, img) || load_door_texture(mlx,
			img));
}

int	get_image_quantity_by_weapon_type(int index)
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
