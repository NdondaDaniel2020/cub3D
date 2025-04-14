/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:43:01 by aquissan          #+#    #+#             */
/*   Updated: 2025/04/14 14:31:54 by nmatondo         ###   ########.fr       */
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

bool	player_near_the_door(t_master *master)
{
	if (master->campus[(int)master->render.pos.x + 1][(int)master->render.pos.y] == 'D')
		return (true);
	if (master->campus[(int)master->render.pos.x - 1][(int)master->render.pos.y] == 'D')
		return (true);
	if (master->campus[(int)master->render.pos.x][(int)master->render.pos.y + 1] == 'D')
		return (true);
	if (master->campus[(int)master->render.pos.x][(int)master->render.pos.y - 1] == 'D')
		return (true);
	return (false);
}

int	controls(void *vars)
{
	// int len;
	t_master	*master;

	master = (t_master *)vars;
	player_animation(master);
	

	// if (master->keyboard.open_door)
	// 	master->door_limit_time_animation = 2;

	// if (master->keyboard.open_door)
	// {
	// 	if (master->door_time_animation >= master->door_limit_time_animation)
	// 	{

	// 		len = get_image_quantity_by_door_type(master->type_door);
	// 		if (master->index_door < (len - 1))
	// 			master->index_door++;
	// 		else
	// 			master->keyboard.open_door = false;
	// 		master->door_time_animation = 0;
	// 	}
	// 	else
	// 		master->door_time_animation++;
	// }

	// if (master->keyboard.open_door == false && master->index_door ==  )
	// {
		
	// }
	
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
