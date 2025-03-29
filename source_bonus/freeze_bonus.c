/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeze_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:20:22 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/29 17:08:07 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	ft_free_stack(t_map *map)
{
	t_map	*tmp;

	while (map)
	{
		tmp = map;
		map = map->next;
		free(tmp->line);
		free(tmp);
	}
}

void	ft_free_master(t_master *master)
{
	if (master->so)
		free(master->so);
	if (master->we)
		free(master->we);
	if (master->ea)
		free(master->ea);
	if (master->no)
		free(master->no);
	if (master->campus)
		ft_freematriz(master->campus);
	free(master);
}

int	ft_freematriz(char **mat)
{
	int	i;

	i = -1;
	if (mat != NULL)
	{
		while (mat && mat[++i])
			free(mat[i]);
		free(mat);
	}
	return (i);
}

int	free_textures(t_master *master)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(master->render.mlx, master->img.textures[i]);
		i++;
	}
	return (0);
}

int	free_player_texture(t_master *master)
{
	int		len;
	t_3d	dim;

	dim.m = 0;
	while (dim.m < 5)
	{
		dim.l = 0;
		len = get_image_quantity_by_weapon_type(dim.m);
		while (dim.l < 3)
		{
			dim.c = 0;
			while (dim.c < len)
			{
				if (master->img.player_texture[dim.m][dim.l][dim.c])
					mlx_destroy_image(master->render.mlx,
						master->img.player_texture[dim.m][dim.l][dim.c]);
				dim.c++;
			}
			dim.l++;
		}
		dim.m++;
	}
	return (0);
}
