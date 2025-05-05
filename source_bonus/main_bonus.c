/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:29:11 by aquissan          #+#    #+#             */
/*   Updated: 2025/05/05 11:50:35 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static int	pre;

t_minilib	set_cardial(t_master *master)
{
	t_minilib	render;
	t_vector	pos;

	pos = get_player_pos(master->campus);
	if (master->campus[(int)pos.x][(int)pos.y] == 'N')
	{
		render.dir = (t_vector){-1, 0};
		render.plane = (t_vector){0, 0.66};
	}
	if (master->campus[(int)pos.x][(int)pos.y] == 'S')
	{
		render.dir = (t_vector){1, 0};
		render.plane = (t_vector){0, -0.66};
	}
	if (master->campus[(int)pos.x][(int)pos.y] == 'E')
	{
		render.dir = (t_vector){0, 1};
		render.plane = (t_vector){0.66, 0};
	}
	if (master->campus[(int)pos.x][(int)pos.y] == 'W')
	{
		render.dir = (t_vector){0, -1};
		render.plane = (t_vector){-0.66, 0};
	}
	return (render);
}

void	preload_pixel_put(t_preload *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	set_step(int pre, int limit)
{
	static int	index_texture;

	if (pre > 100 && pre < 200)
	{
		if ((pre % 100) == (1 * (index_texture + 1)))
			index_texture++;
		if (index_texture >= 7)
			index_texture--;
	}
	if (pre > 200)
	{
		if ((pre % 100) == (8 * (index_texture + 1)))
			index_texture++;
		if (index_texture >= limit)
			index_texture--;
	}
	return (index_texture);
}

int	put_logo(t_master *master, int x, int y)
{
	t_intvector	tex;
	int			color;
	t_image		img;

	pre++;
		img = master->preload.logo[set_step(pre, 13)];
	tex = (t_intvector){0, 0};
	while (tex.x < img.width && tex.x < SCREEN_WIDTH)
	{
		tex.y = 0;
		while (tex.y < img.height && tex.y < SCREEN_HEIGHT)
		{
			color = *(unsigned int *)(img.addr + (tex.y * img.line_length
						+ tex.x * (img.bits_per_pixel / 8)));
			if (!((color & 0x00FFFFFF) == 0x000000))
				preload_pixel_put(&master->preload, x + tex.x, y + tex.y,
					color);
			tex.y++;
		}
		tex.x++;
	}
	return (0);
}

int	preload(t_master *master)
{
	t_intvector	tex;
	int			color;
	int x, y;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			tex.x = (x * master->preload.background.width) / SCREEN_WIDTH;
			tex.y = (y * master->preload.background.height) / SCREEN_HEIGHT;
			color = *(unsigned int *)(master->preload.background.addr + (tex.y
						* master->preload.background.line_length + tex.x
						* (master->preload.background.bits_per_pixel / 8)));
			preload_pixel_put(&master->preload, x, y++, color);
		}
	}
	put_logo(master, (SCREEN_WIDTH / 2) - (master->preload.logo[0].width / 2),
		(SCREEN_HEIGHT / 2) - (master->preload.logo[0].height * 1.8));
	return (mlx_put_image_to_window(master->render.mlx, master->render.win,
			master->preload.img, 0, 0), 0);
}

int	ft_game(t_master *master)
{
	t_minilib	render;
	t_data		img;

	init_data_struct(&img);
	render = set_cardial(master);
	render.pos = get_player_pos(master->campus);
	render.pos = (t_vector){render.pos.x + 0.5, render.pos.y + 0.5};
	render.mlx = mlx_init();
	if (!render.mlx)
		return (ft_free_master(master), printerror("Connection mlx failed"), 1);
	if (load_all_texteres(render.mlx, &img, master))
		return (mlx_destroy_display(render.mlx), free(render.mlx),
			ft_free_master(master), exit(1), 1);
	render.win = mlx_new_window(render.mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"ODYSSEY 2.0");
	img.img = mlx_new_image(render.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	master->render = render;
	master->img = img;
	if (master->game_started)
		mlx_put_image_to_window(master->render.mlx, render.win, img.img, 0, 0);
	return (wait_hooks(master), mlx_loop_hook(master->render.mlx, controls,
			master), mlx_loop(render.mlx), 0);
}

int	main(int ac, char *av[])
{
	t_master	*master;
	t_map		*map;

	if (ac == 2 && av)
	{
		if (SCREEN_WIDTH < 150)
			return (printerror("Window width too small"), 1);
		if (SCREEN_HEIGHT < 150)
			return (printerror("Window height too small"), 1);
		if (SPEED <= 0)
			return (printerror("The player speed must be bigger than 0"), 1);
		map = ft_read_file(av[1]);
		if (!map)
			return (1);
		master = get_master(map);
		ft_free_stack(map);
		master->rotate_angle = 0;
		if (master->wrongmap == 0)
			return (ft_game(master));
		else
			return (ft_free_master(master), 1);
	}
	else
		return (printerror("Usage: ./<executable> <map_way>"), 1);
	return (0);
}
