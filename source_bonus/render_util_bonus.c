/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_util_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:47:43 by nmatondo          #+#    #+#             */
/*   Updated: 2025/04/11 10:45:25 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	wall_and_door_dda(t_master *master, int *hitSide, t_intvector *step)
{
	dda(master, hitSide, step, &master->wallmappos);
	door_dda(master, hitSide, step, &master->render.door_map_pos);
}

void	set_wall_and_door_height(t_master *master, t_minilib *render,
	int hitside, t_intvector step)
{
	setwallheight(render, hitside, master->wallmappos, step);
	set_door_height(render, &hitside, master->render.door_map_pos, step);
}

void	draw_texture_and_door(int hitSide, t_intvector *pos,
	t_data *img, t_master *master)
{
	draw_texture(hitSide, pos, img, master);
	draw_door(hitSide, pos, img, master);
}
