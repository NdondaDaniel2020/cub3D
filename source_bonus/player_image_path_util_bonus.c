/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_image_path_util_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:10:10 by nmatondo          #+#    #+#             */
/*   Updated: 2025/04/28 11:17:42 by aquissan         ###   ########.fr       */
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

int	load_all_texteres(void *mlx, t_data *img, t_master *master)
{
	return (load_ceil_and_floor_texture(mlx, img) || load_textures(mlx, img,
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
