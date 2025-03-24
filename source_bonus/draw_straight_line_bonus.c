/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_straight_line_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-20 12:10:04 by nmatondo          #+#    #+#             */
/*   Updated: 2025-03-20 12:10:04 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	draw_big_pixel(t_master *master, int size, int x, int y, int color) /* falha */
{
	int i;
	int j;

	i = 0;
    while (i < size)
    {
		j = 0;
        while (j < size)
        {
			my_mlx_pixel_put(&master->img, x + i, y + j, color);
			j++;
        }
		i++;
    }
}

void	init_bresenham(t_bresenham *bresenham)
{
    bresenham->dx = bresenham->x_end - bresenham->x_ini;
    bresenham->dy = bresenham->y_end - bresenham->y_ini;
    bresenham->x = bresenham->x_ini;
    bresenham->y = bresenham->y_ini;
	bresenham->inc_x = -1;
	bresenham->inc_y = -1;
	if (bresenham->dx > 0)
    	bresenham->inc_x = 1;
	if (bresenham->dy > 0)
    	bresenham->inc_y = 1;
    bresenham->dx = abs(bresenham->dx);
    bresenham->dy = abs(bresenham->dy);
}

void	draw_positive_straight_line(t_master *master, t_bresenham *bresenham, int size, int color)
{
	int	p;

	p = 2 * bresenham->dy - bresenham->dx;
	while (bresenham->x != bresenham->x_end)
	{
		draw_big_pixel(master, size, bresenham->x, bresenham->y, color);
		bresenham->x += bresenham->inc_x;
		if (p >= 0)
		{
			bresenham->y += bresenham->inc_y;
			p -= 2 * bresenham->dx;
		}
		p += 2 * bresenham->dy;
	}
}

void	draw_negative_straight_line(t_master *master, t_bresenham *bresenham, int size, int color)
{
	int	p;

	p = 2 * bresenham->dx - bresenham->dy;
	while (bresenham->y != bresenham->y_end)
	{
		draw_big_pixel(master, size, bresenham->x, bresenham->y, color);
		bresenham->y += bresenham->inc_y;
		if (p >= 0)
		{
			bresenham->x += bresenham->inc_x;
			p -= 2 * bresenham->dy;
		}
		p += 2 * bresenham->dx;
	}
}

void	draw_straight_line(t_master *master, t_bresenham *line, int size, int color)
{
	init_bresenham(line);
    if (line->dx > line->dy)
		draw_positive_straight_line(master, line, size, color);
    else
		draw_negative_straight_line(master, line, size, color);
	draw_big_pixel(master, size, line->x, line->y, color);
}
