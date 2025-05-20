/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeze_2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 12:48:25 by nmatondo          #+#    #+#             */
/*   Updated: 2025/05/20 13:20:41 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	free_door_texture(void *mlx, t_data *img)
{
	int	l;
	int	c;
	int	len;

	l = 0;
	while (l < 3)
	{
		c = 0;
		len = get_image_quantity_by_door_type(l);
		while (c < len)
		{
			mlx_destroy_image(mlx, img->door_texture[l][c]);
			c++;
		}
		l++;
	}
}

void	free_cardials(t_master *master)
{
	if (master->so)
	{
		free(master->so);
		master->so = NULL;
	}
	if (master->we)
	{
		free(master->we);
		master->we = NULL;
	}
	if (master->ea)
	{
		free(master->ea);
		master->ea = NULL;
	}
	if (master->no)
	{
		free(master->no);
		master->no = NULL;
	}
}
