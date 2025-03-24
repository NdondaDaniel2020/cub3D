/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:34:47 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/24 12:35:25 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	wait_hooks(t_master *master)
{
	mlx_hook(master->render.win, 2, 1L << 0, key_hook, master);
	mlx_hook(master->render.win, 3, 1L << 1, key_release, master);
	mlx_hook(master->render.win, 17, 1L << 1, key_exit, master);
	mlx_hook(master->render.win, 6, 1L << 6, mousemove, master);
	return (0);
}
