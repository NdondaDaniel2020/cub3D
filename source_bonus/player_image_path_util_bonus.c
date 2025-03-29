/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_image_path_util_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:10:10 by nmatondo          #+#    #+#             */
/*   Updated: 2025/03/29 17:34:26 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	load_all_texteres(void *mlx, t_data *img, t_master *master)
{
	return (load_textures(mlx, img, master)
		|| load_player_texture(mlx, img));
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
