/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_util_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:47:43 by nmatondo          #+#    #+#             */
/*   Updated: 2025/04/11 14:57:15 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	wall_and_door_dda(t_master *master, t_intvector *step)
{
	master->wall_hitside = 0;
	master->door_hitside = 0;
	dda(master, &master->wall_hitside, step, &master->wallmappos);
	door_dda(master, &master->door_hitside, step, &master->render.door_map_pos);
}

void	set_wall_and_door_height(t_master *master, t_minilib *render, t_intvector step)
{
	setwallheight(render, master->wall_hitside, master->wallmappos, step);
	set_door_height(render, &master->door_hitside, master->render.door_map_pos, step);
}

void	draw_texture_and_door(t_intvector *pos, t_data *img, t_master *master)
{
	draw_texture(pos, img, master);
	draw_door(pos, img, master);
}
