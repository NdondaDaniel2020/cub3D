/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:34:47 by aquissan          #+#    #+#             */
/*   Updated: 2025/04/01 15:54:49 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static int	key_weapon(int keycode, t_master *master)
{
	if (keycode == ONE && master->dimension.l != 0)
		master->dimension.m = 0;
	if (keycode == TWO && master->dimension.l != 0)
		master->dimension.m = 1;
	if (keycode == THREE && master->dimension.l != 0)
		master->dimension.m = 2;
	if (keycode == FOUR && master->dimension.l != 0)
		master->dimension.m = 3;
	if (keycode == FIVE && master->dimension.l != 0)
		master->dimension.m = 4;
	if (keycode == SZERO && master->dimension.l != 0)
		master->keyboard.mouse_left = true;
	return (0);
}

int	key_hook(int keycode, t_master *master)
{
	if (keycode == ESC)
	{
		return (free_textures(master), free_player_texture(master),
			mlx_destroy_image(master->render.mlx, master->img.img),
			mlx_destroy_window(master->render.mlx, master->render.win),
			mlx_destroy_display(master->render.mlx), free(master->render.mlx),
			ft_free_master(master), exit(0), 0);
	}
	if (keycode == RRIGHT)
		master->keyboard.r_right = true;
	if (keycode == RUP)
		master->keyboard.r_up = true;
	if (keycode == RDOWN)
		master->keyboard.r_down = true;
	if (keycode == RLEFT)
		master->keyboard.r_left = true;
	if (keycode == RIGHT)
		master->keyboard.right = true;
	if (keycode == DOWN)
		master->keyboard.down = true;
	if (keycode == UP)
		master->keyboard.up = true;
	if (keycode == LEFT)
		master->keyboard.left = true;
	return (key_weapon(keycode, master), 0);
}

int	key_release(int keycode, t_master *master)
{
	if (keycode == RRIGHT)
		master->keyboard.r_right = false;
	if (keycode == RUP)
		master->keyboard.r_up = false;
	if (keycode == RDOWN)
		master->keyboard.r_down = false;
	if (keycode == RLEFT)
		master->keyboard.r_left = false;
	if (keycode == RIGHT)
		master->keyboard.right = false;
	if (keycode == DOWN)
		master->keyboard.down = false;
	if (keycode == UP)
		master->keyboard.up = false;
	if (keycode == LEFT)
		master->keyboard.left = false;
	return (0);
}

int	mouse_press(int button, int x, int y, t_master *master)
{
	(void)x, (void)y;
	if (button == 1)
		master->keyboard.mouse_left = true;
	return (0);
}

int	wait_hooks(t_master *master)
{
	mlx_hook(master->render.win, 2, 1L << 0, key_hook, master);
	mlx_hook(master->render.win, 3, 1L << 1, key_release, master);
	mlx_hook(master->render.win, 17, 1L << 1, key_exit, master);
	mlx_hook(master->render.win, 6, 1L << 6, mousemove, master);
	mlx_hook(master->render.win, 4, 1L << 2, mouse_press, master);
	return (0);
}
