/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pos_door_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:03:30 by nmatondo          #+#    #+#             */
/*   Updated: 2025/04/16 13:29:06 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

t_intvector	get_pos_door(t_master *master)
{
	bool		door;
	t_intvector	pos;

	door = more_than_one_door(master);
	if (door)
	{
		pos = get_the_position_of_the_door_that_is_in_front_of_the_player(
				master);
		if (pos.x != -1 && pos.y != -1)
			return (pos);
	}
	return (get_the_position_of_the_door_around_the_player(master));
}
