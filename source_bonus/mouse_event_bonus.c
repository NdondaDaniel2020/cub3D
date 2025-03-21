/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:13:43 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/21 13:43:27 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	mousemove(int x, int y, t_master *master)
{
	int			div;
	static int	posx;

	div = 4;
	(void)y;
	if (posx < x)
	{
		master->render.dir = rotate_vector(master->render.dir, (SPEED / div));
		master->render.plane = rotate_vector(master->render.plane, (SPEED
					/ div));
	}
	else if (posx > x)
	{
		master->render.dir = rotate_vector(master->render.dir, -(SPEED / div));
		master->render.plane = rotate_vector(master->render.plane, -(SPEED
					/ div));
	}
	posx = x;
	return (0);
}
