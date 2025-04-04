/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:43:01 by aquissan          #+#    #+#             */
/*   Updated: 2025/04/04 12:59:04 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	rotate_x(t_master *master)
{
	if (master->keyboard.r_right)
	{
		master->render.dir = rotate_vector(master->render.dir, -SPEED);
		master->render.plane = rotate_vector(master->render.plane, -SPEED);
	}
	if (master->keyboard.r_left)
	{
		master->render.dir = rotate_vector(master->render.dir, SPEED);
		master->render.plane = rotate_vector(master->render.plane, SPEED);
	}
}

void	move_x(t_master *master)
{
	t_vector	dir;
	t_minilib	*rd;

	rd = &master->render;
	if (master->keyboard.right)
	{
		dir = (t_vector){rd->dir.y, -rd->dir.x};
		if (master->campus[(int)(rd->pos.x + dir.x * (SPEED
					+ 0.1))][(int)(rd->pos.y)] != '1')
			rd->pos.x += dir.x * SPEED;
		if (master->campus[(int)(rd->pos.x)][(int)(rd->pos.y + dir.y * (SPEED
					+ 0.1))] != '1')
			rd->pos.y += dir.y * SPEED;
	}
	if (master->keyboard.left)
	{
		dir = (t_vector){-rd->dir.y, rd->dir.x};
		if (master->campus[(int)(rd->pos.x + dir.x * (SPEED
					+ 0.1))][(int)(rd->pos.y)] != '1')
			rd->pos.x += dir.x * SPEED;
		if (master->campus[(int)(rd->pos.x)][(int)(rd->pos.y + dir.y * (SPEED
					+ 0.1))] != '1')
			rd->pos.y += dir.y * SPEED;
	}
}

void	move_y(t_master *master)
{
	t_vector	dir;
	t_minilib	*rd;

	rd = &master->render;
	if (master->keyboard.up)
	{
		dir = (t_vector){rd->dir.x, rd->dir.y};
		if (master->campus[(int)(rd->pos.x + dir.x * (SPEED
					+ 0.1))][(int)(rd->pos.y)] != '1')
			rd->pos.x += dir.x * SPEED;
		if (master->campus[(int)(rd->pos.x)][(int)(rd->pos.y + dir.y * (SPEED
					+ 0.1))] != '1')
			rd->pos.y += dir.y * SPEED;
	}
	if (master->keyboard.down)
	{
		dir = (t_vector){-rd->dir.x, -rd->dir.y};
		if (master->campus[(int)(rd->pos.x + dir.x * (SPEED
					+ 0.1))][(int)(rd->pos.y)] != '1')
			rd->pos.x += dir.x * SPEED;
		if (master->campus[(int)(rd->pos.x)][(int)(rd->pos.y + dir.y * (SPEED
					+ 0.1))] != '1')
			rd->pos.y += dir.y * SPEED;
	}
}

int	rotate_y(t_master *master)
{
	if (master->keyboard.r_up)
		master->view_high += SPEED * ROTATE_SPEED;
	if (master->keyboard.r_down)
		master->view_high -= SPEED * ROTATE_SPEED;
	if (master->view_high > SCREEN_HEIGHT / 3)
		master->view_high = SCREEN_HEIGHT / 3;
	if (master->view_high < -SCREEN_HEIGHT / 3)
		master->view_high = -SCREEN_HEIGHT / 3;
	return (0);
}

int	controls(void *vars)
{
	t_master	*master;

	master = (t_master *)vars;
	player_animation(master);
	move_y(master);
	move_x(master);
	rotate_x(master);
	rotate_y(master);
	renderization(&master->render, master, &master->img);
	draw_small_map(master);
	draw_player(master);
	draw_crosshair(master);
	mlx_put_image_to_window(master->render.mlx, master->render.win,
		master->img.img, 0, 0);
	return (0);
}
