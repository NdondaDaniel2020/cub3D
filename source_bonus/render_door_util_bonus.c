/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_door_util_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:11:30 by marvin            #+#    #+#             */
/*   Updated: 2025/04/11 20:11:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

bool	door_found(t_master *master, t_intvector pos)
{
	if (master->campus[pos.x][pos.y] == 'D'
		|| master->campus[pos.x][pos.y] == 'd'
		|| master->campus[pos.x][pos.y] == 'F'
		|| master->campus[pos.x][pos.y] == 'f'
		|| master->campus[pos.x][pos.y] == 'G'
		|| master->campus[pos.x][pos.y] == 'g'
		|| master->campus[pos.x][pos.y] == 'H'
		|| master->campus[pos.x][pos.y] == 'h'
		|| master->campus[pos.x][pos.y] == 'J'
		|| master->campus[pos.x][pos.y] == 'j'
		|| master->campus[pos.x][pos.y] == 'K'
		|| master->campus[pos.x][pos.y] == 'k')
		return (true);
	return (false);
}

bool	valid_character_pass(char chr)
{
	if (chr != '1' && chr != 'D' && chr != 'F' && chr != 'G'
		&& chr != 'H' && chr != 'J' && chr != 'K')
		return (true);
	return (false);
}

static void	is_door(t_master *master, bool *hit, t_intvector *door_map_pos)
{
	if (door_found(master, (t_intvector)(*door_map_pos)))
	{
		master->render.door_object_touched
			= master->campus[(*door_map_pos).x][(*door_map_pos).y];
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
