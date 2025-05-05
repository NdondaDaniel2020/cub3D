/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preload_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:23:59 by aquissan          #+#    #+#             */
/*   Updated: 2025/05/05 13:29:08 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

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
