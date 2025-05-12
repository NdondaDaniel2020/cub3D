/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_small_map_util_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:10:04 by nmatondo          #+#    #+#             */
/*   Updated: 2025/05/12 11:50:55 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	draw_map_util(t_master *master, t_vector pos, int i1, int i2)
{
	int	len_matrix;

	len_matrix = 0;
	while (master->campus[len_matrix])
		len_matrix++;
	if (i1 < 0 || i2 < 0 || i1 >= len_matrix
		|| i2 >= (int)ft_strlen(master->campus[i1]))
		draw_big_pixel(master, PIXEL_SIZE, pos, 0x3c3c3c);
	else if (master->campus[i1][i2] == '1')
		draw_big_pixel(master, PIXEL_SIZE, pos, 0x52be80);
	else if (master->campus[i1][i2] == 'D' || master->campus[i1][i2] == 'F'
			|| master->campus[i1][i2] == 'f' || master->campus[i1][i2] == 'G'
			|| master->campus[i1][i2] == 'g' || master->campus[i1][i2] == 'H'
			|| master->campus[i1][i2] == 'h' || master->campus[i1][i2] == 'J'
			|| master->campus[i1][i2] == 'j' || master->campus[i1][i2] == 'K'
			|| master->campus[i1][i2] == 'k')
		draw_big_pixel(master, PIXEL_SIZE, pos, 0xecb4335);
	else if (master->campus[i1][i2] == 'd')
		draw_big_pixel(master, PIXEL_SIZE, pos, 0x2471a3);
	else if (master->campus[i1][i2] != '1')
		draw_big_pixel(master, PIXEL_SIZE, pos, 0x3c3c3c);
}
