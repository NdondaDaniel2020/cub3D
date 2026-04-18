/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:45:57 by aquissan          #+#    #+#             */
/*   Updated: 2025/04/02 08:44:58 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static unsigned int	darken_color(unsigned int color, int percentage)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (int)(r * (100 - percentage) / 100);
	g = (int)(g * (100 - percentage) / 100);
	b = (int)(b * (100 - percentage) / 100);
	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

unsigned int	get_color(int hitSide, t_texture *texture, t_data *img)
{
	unsigned int	color;

	color = *(unsigned int *)(img->tex_addr[texture->index] + (texture->y
				* img->tex_line_length[texture->index] + texture->x
				* (img->tex_bits_per_pixel[texture->index] / 8)));
	if (hitSide == 1)
		color = darken_color(color, 30);
	return (color);
}

int	get_draw_start_position(int wallheight, t_master *master)
{
	int	drawstart;
	int	jump_offset;

	jump_offset = master->jump_z * wallheight;
	drawstart = -wallheight / 2 + (SCREEN_HEIGHT / 2) + master->view_high + jump_offset;
	if (drawstart < 0)
		drawstart = 0;
	if (drawstart > SCREEN_HEIGHT)
		drawstart = SCREEN_HEIGHT;
	return (drawstart);
}

int	get_draw_end_position(int wallheight, t_master *master)
{
	int	draw_end;
	int	jump_offset;

	jump_offset = master->jump_z * wallheight;
	draw_end = wallheight / 2 + (SCREEN_HEIGHT / 2) + master->view_high + jump_offset;
	if (draw_end > SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT;
	if (draw_end < 0)
		draw_end = 0;
	return (draw_end);
}

int	get_texture_index(int hitSide, t_vector rayDir)
{
	if (hitSide == 1)
	{
		if (rayDir.y > 0)
			return (2);
		else
			return (3);
	}
	else
	{
		if (rayDir.x > 0)
			return (1);
		else
			return (0);
	}
}
