/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:13:43 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/24 12:18:39 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	rotate_up(t_master *master, int div)
{
	master->view_high += (SPEED * ROTATE_SPEED) / div;
	return (0);
}

int	rotate_down(t_master *master, int div)
{
	master->view_high -= (SPEED * ROTATE_SPEED) / div;
	return (0);
}

int	mousemove(int x, int y, t_master *master)
{
	int			div;
	static int	posx;
	static int	posy;

	div = 4;
	if (posx > x)
	{
		master->render.dir = rotate_vector(master->render.dir, (SPEED / div));
		master->render.plane = rotate_vector(master->render.plane, (SPEED
					/ div));
	}
	else if (posx < x)
	{
		master->render.dir = rotate_vector(master->render.dir, -(SPEED / div));
		master->render.plane = rotate_vector(master->render.plane, -(SPEED
					/ div));
	}
	if (posy > y)
		rotate_up(master, div);
	if (posy < y)
		rotate_down(master, div);
	posx = x;
	posy = y;
	return (0);
}
