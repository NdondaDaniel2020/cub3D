/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeze.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:20:22 by aquissan          #+#    #+#             */
/*   Updated: 2025/05/20 13:58:46 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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

void	ft_free_master(t_master *master)
{
	free_cardials(master);
	if (master->campus)
	{
		ft_freematriz(master->campus);
		master->campus = NULL;
	}
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

void	free_textures(t_master *master)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(master->render.mlx, master->img.textures[i]);
		i++;
	}
}
