/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_door_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:32:11 by aquissan          #+#    #+#             */
/*   Updated: 2025/04/11 10:45:35 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	is_door(t_master *master, bool *hit, t_intvector *door_map_pos)
{
	if (master->campus[(*door_map_pos).x][(*door_map_pos).y] == 'D')
	{	
		master->render.is_door = true;
		*hit = true;
	}
	if (master->campus[(*door_map_pos).x][(*door_map_pos).y] == '1')
		*hit = true;
}

void	door_dda(t_master *master, int *hitSide, t_intvector *step,
	t_intvector *door_map_pos)
{
	bool		hit;
	t_vector	ddalinesize;

	ddalinesize = (t_vector){master->render.disttoside.x,
		master->render.disttoside.y};
	*door_map_pos = master->render.mappos;
	master->render.is_door = false;
	hit = false;
	while (!hit)
	{
		if (ddalinesize.x < ddalinesize.y)
		{
			(*door_map_pos).x += step->x;
			ddalinesize.x += master->render.deltadist.x;
			*hitSide = 0;
		}
		else
		{
			(*door_map_pos).y += step->y;
			ddalinesize.y += master->render.deltadist.y;
			*hitSide = 1;
		}
		is_door(master, &hit, door_map_pos);
	}
}

void	set_door_height(t_minilib *render, int *hitside,
	t_intvector door_map_pos, t_intvector step)
{
	if (*hitside == 0)
		render->perpendicular_dist_door = fabs((door_map_pos.x - render->pos.x
			+ ((1 - step.x) / 2.0)) / render->raydir.x);		
	else
		render->perpendicular_dist_door = fabs((door_map_pos.y - render->pos.y
			+ ((1 - step.y) / 2.0)) / render->raydir.y);
	render->door_height = SCREEN_HEIGHT / render->perpendicular_dist_door;
}

unsigned int	get_door_color(t_master *master,
	t_texture *texture, t_data *img)
{
	unsigned int	color;

	color = *(unsigned int *)(img->door_texture_addr
			[master->index_door][texture->index] + (texture->y
		* img->door_texture_line_length[master->index_door][texture->index]
		+ texture->x * (img->door_texture_bits_per_pixel
			[master->index_door][texture->index] / 8)));

	return (color);
}

int	get_x_coordinate_door_texture(int index, int hitSide,
	t_master *master, t_data *img)
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
	texx = (int)(wallx * (double)img->door_texture_width
		[master->index_door][index]);
	if ((hitSide == 0 && master->render.raydir.x > 0)
		|| (hitSide == 1 && master->render.raydir.y < 0))
		texx = img->door_texture_width[master->index_door][index] - texx - 1;
	return (texx);
}


void	draw_door(int hitSide, t_intvector *pos, t_data *img, t_master *master)
{
	int			start_door;
	int			end_door;
	int			start;
	int			end;
	t_texture	texture_door;
	t_texture	texture;

	(void)start;
	(void)end;
	if (master->render.is_door)
	{
		// door //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		start_door = get_draw_start_position(master->render.door_height, master);
		end_door = get_draw_end_position(master->render.door_height, master);
		// door //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// wall //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		start = get_draw_start_position(master->render.wallheight, master);
		end = get_draw_end_position(master->render.wallheight, master);
		// wall //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




		// door //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		texture_door.index = 0;
		master->index_door = 0;
		texture_door.x = get_x_coordinate_door_texture(texture_door.index, hitSide, master, img);
		texture_door.step = 1.0 * img->door_texture_height[master->index_door][texture_door.index] / master->render.door_height;
		texture_door.pos = ((start_door - master->view_high) - SCREEN_HEIGHT / 2 + master->render.door_height / 2) * texture_door.step;
		// door //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// wall //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		texture.index = get_texture_index(hitSide, master->render.raydir);
		texture.x = get_x_coordinate_texture(texture.index, hitSide, master, img);
		texture.step = 1.0 * img->tex_height[texture.index] / master->render.wallheight;
		texture.pos = ((start - master->view_high) - SCREEN_HEIGHT / 2 + master->render.wallheight / 2) * texture.step;	
		// wall //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		

		pos->y = start_door;
		while (pos->y < end_door)
		{
		// door //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			texture_door.y = (int)texture_door.pos % (img->door_texture_height[master->index_door][texture_door.index] - 1);
			texture_door.pos += texture_door.step;
			texture_door.color = get_door_color(master, &texture_door, img);
		// door //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// wall //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
			texture.y = (int)texture.pos % (img->tex_height[texture.index] - 1);
			texture.pos += texture.step;
			texture.color = get_color(hitSide, &texture, img);
		// wall //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		
		
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// my_mlx_pixel_put(img, pos->x, pos->y++, texture_door.color);
			if ((texture_door.color & 0xFF000000) == 0)
				my_mlx_pixel_put(img, pos->x, pos->y++, texture_door.color);
			else
			{
				if (pos->y < start)
					my_mlx_pixel_put(img, pos->x, pos->y++, master->c);
				else if (pos->y > end)
					my_mlx_pixel_put(img, pos->x, pos->y++, master->f);
				else
					my_mlx_pixel_put(img, pos->x, pos->y++, texture.color);
			}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
	}
}
