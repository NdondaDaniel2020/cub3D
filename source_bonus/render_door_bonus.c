/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_door_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:32:11 by aquissan          #+#    #+#             */
/*   Updated: 2025/04/16 13:51:08 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

unsigned int	get_door_color(t_master *master, t_texture *texture,
	t_data *img)
{
	unsigned int	color;

	(void)master;
	color = *(unsigned int *)(img->door_texture_addr
		[master->type_door][master->index_door] + (texture->y
				* img->door_texture_line_length[master->type_door]
			[master->index_door]
				+ texture->x * (img->door_texture_bits_per_pixel
				[master->type_door][master->index_door] / 8)));
	return (color);
}

int	get_x_coordinate_door_texture(int hitSide, t_master *master, t_data *img)
{
	int		texx;
	double	wallx;

	if (hitSide == 0)
		wallx = master->render.pos.y
			+ master->render.perpendicular_dist_door * master->render.raydir.y;
	else
		wallx = master->render.pos.x
			+ master->render.perpendicular_dist_door * master->render.raydir.x;
	wallx -= floor(wallx);
	texx = (int)(wallx * (double)img->door_texture_width[
			master->type_door][master->index_door]);
	if ((hitSide == 0 && master->render.raydir.x > 0)
		|| (hitSide == 1 && master->render.raydir.y < 0))
		texx = img->door_texture_width[master->type_door][master->index_door]
			- texx - 1;
	return (texx);
}

static void	draw_door_texture_in_draw_door(t_intvector *pos, t_data *img,
	t_master *master, t_draw_door	*draw)
{
	// master->render.door_height
	draw->start_door = get_draw_start_position(master->render.door_height,
			master);
	draw->end_door = get_draw_end_position(master->render.door_height, master);
	draw->texture_door.index = 0;
	draw->texture_door.x = get_x_coordinate_door_texture(master->door_hitside,
			master, img);
	draw->texture_door.step = 1.0 * img->door_texture_height[
		master->type_door][master->index_door] / master->render.door_height;
	draw->texture_door.pos = ((draw->start_door - master->view_high)
			- SCREEN_HEIGHT / 2 + master->render.door_height / 2)
		* draw->texture_door.step;
	pos->y = draw->start_door;
	while (pos->y < draw->end_door)
	{
		draw->texture_door.y = (int)draw->texture_door.pos
			% (img->door_texture_height[
				master->type_door][master->index_door] - 1);
		draw->texture_door.pos += draw->texture_door.step;
		draw->texture_door.color = get_door_color(master,
				&draw->texture_door, img);
		if ((draw->texture_door.color & 0xFF000000) == 0)
			my_mlx_pixel_put(img, pos->x, pos->y, draw->texture_door.color);
		pos->y++;
	}
}

static void	draw_wall_texture_in_draw_door(t_intvector *pos, t_data *img,
	t_master *master, t_draw_door	*draw)
{
	draw->start_wall = get_draw_start_position(master->render.wallheight,
			master);
	draw->end_wall = get_draw_end_position(master->render.wallheight, master);
	draw->texture_wall.index = get_texture_index(master->wall_hitside,
			master->render.raydir);
	draw->texture_wall.x = get_x_coordinate_texture(draw->texture_wall.index,
			master->wall_hitside, master, img);
	draw->texture_wall.step = 1.0 * img->tex_height[draw->texture_wall.index]
		/ master->render.wallheight;
	draw->texture_wall.pos = ((draw->start_wall - master->view_high)
			- SCREEN_HEIGHT / 2 + master->render.wallheight / 2)
		* draw->texture_wall.step;
	pos->y = draw->start_wall;
	while (pos->y < draw->end_wall)
	{
		draw->texture_wall.y = (int)draw->texture_wall.pos % (img->tex_height[
				draw->texture_wall.index] - 1);
		draw->texture_wall.pos += draw->texture_wall.step;
		draw->texture_wall.color = get_color(master->wall_hitside,
				&draw->texture_wall, img);
		if (pos->y < draw->start_door || pos->y > draw->end_door)
			my_mlx_pixel_put(img, pos->x, pos->y, draw->texture_wall.color);
		pos->y++;
	}
}

void	draw_door(t_intvector *pos, t_data *img, t_master *master)
{
	t_draw_door	draw;

	if (master->render.is_door)
	{
		master->type_door = 0;
		master->index_door = get_image_index_by_character_type(master);
		draw_door_texture_in_draw_door(pos, img, master, &draw);
		draw_wall_texture_in_draw_door(pos, img, master, &draw);
	}
}
