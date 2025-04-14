/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_small_map_util_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:10:04 by nmatondo          #+#    #+#             */
/*   Updated: 2025/04/14 14:44:49 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	draw_map_util(t_master *master, t_vector pos, int i1, int i2)
{
	if (master->campus[i1][i2] == '1')
		draw_big_pixel(master, PIXEL_SIZE, pos, 0x52be80);
	else if (master->campus[i1][i2] == 'D')
		draw_big_pixel(master, PIXEL_SIZE, pos, 0xecb4335);
	else if (master->campus[i1][i2] == 'd')
		draw_big_pixel(master, PIXEL_SIZE, pos, 0x2471a3);
	else if (master->campus[i1][i2] != '1')
		draw_big_pixel(master, PIXEL_SIZE, pos, 0x3c3c3c);
}
