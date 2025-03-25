/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_small_map_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-20 12:10:04 by nmatondo          #+#    #+#             */
/*   Updated: 2025-03-20 12:10:04 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"
#define PIXEL_SIZE 15

void	draw_map(t_master *master, t_area *area)
{
	int i1;
	int i2;
	t_vector	aux;
	t_vector	pos;

	aux.y = 1;
	i1 = area->ini_x;
	while (i1 <= area->end_x)
	{
		aux.x = 1;
		i2 = area->ini_y;
		while (i2 <= area->end_y)
		{
			pos.x = aux.x * PIXEL_SIZE;
			pos.y = aux.y * PIXEL_SIZE;
			if (master->campus[i1][i2] == '1')
				draw_big_pixel(master, PIXEL_SIZE, pos, 0x52be80);
			else if (master->campus[i1][i2] != '1')
				draw_big_pixel(master, PIXEL_SIZE, pos, 0x3c3c3c);
			i2++;
			aux.x++;
		}
		i1++;
		aux.y++;
	}
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
