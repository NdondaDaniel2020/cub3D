/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_small_map_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:10:04 by nmatondo          #+#    #+#             */
/*   Updated: 2025/03/25 12:42:28 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"
#define PIXEL_SIZE 5

void	draw_map(t_master *master, t_area *area)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	y = 1;
	while (area->ini_x <= area->end_x)
	{
		x = 1;
		i = area->ini_y;
		while (i <= area->end_y)
		{
			if (master->campus[area->ini_x][i] == '1')
			{
				draw_big_pixel(master, PIXEL_SIZE, (t_intvector){x * PIXEL_SIZE,
					y * PIXEL_SIZE}, 0x52be80);
			}
			else if (master->campus[area->ini_x][i] != '1')
			{
				draw_big_pixel(master, PIXEL_SIZE, (t_intvector){x * PIXEL_SIZE,
					y * PIXEL_SIZE}, 0x3c3c3c);
			}
			if ((int)master->render.pos.x == area->ini_x
				&& (int)master->render.pos.y == i)
			{
				draw_big_pixel(master, PIXEL_SIZE, (t_intvector){x * PIXEL_SIZE,
					y * PIXEL_SIZE}, 0xFF0000);
			}
			i++;
			x++;
		}
		area->ini_x++;
		y++;
	}
	printf("[%f, %f]\n", master->render.pos.x, master->render.pos.y);
}

void	draw_small_map(t_master *master)
{
	t_area	area;
	t_area	extra;
	t_size	size;

	size.height = get_height_player_line(master) - 1;
	size.width = get_width_player_line(master) - 1;
	area = (t_area){0, 0, 0, 0};
	extra = (t_area){0, 0, 0, 0};
	set_area_value(master, &size, &area, &extra);
	adjust_initial_area_values(master, &area, &extra);
	adjust_final_area_values(master, &area, &extra);
	draw_map(master, &area);
}
