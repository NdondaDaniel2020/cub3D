/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:55:53 by aquissan          #+#    #+#             */
/*   Updated: 2025/05/20 10:55:35 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define CYAN "\033[36m"
# define READ O_RDONLY
# define WRITE O_WRONLY
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "get_next_line.h"
# include <errno.h>
# include <math.h>
# include <stdbool.h>
# include <string.h>

# if !defined SCREEN_WIDTH
#  define SCREEN_WIDTH 800
# endif
# if !defined SCREEN_HEIGHT
#  define SCREEN_HEIGHT 600
# endif
# if !defined SPEED
#  define SPEED 0.010
# endif
# define PI 3.14
# define ESC 65307
# define RRIGHT 65363
# define RUP 65362
# define RDOWN 65364
# define RLEFT 65361
# define UP 119
# define LEFT 97
# define RIGHT 100
# define DOWN 115

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

typedef struct s_map
{
	char			*line;
	struct s_map	*next;
}					t_map;

typedef struct s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct s_intvector
{
	int				x;
	int				y;
}					t_intvector;

typedef struct s_keyboard
{
	bool			right;
	bool			left;
	bool			down;
	bool			up;
	bool			r_right;
	bool			r_left;
	bool			r_down;
	bool			r_up;
}					t_keyboard;

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;

	void			*textures[4];
	char			*tex_addr[4];
	char			*tex_paths[4];
	int				tex_width[4];
	int				tex_height[4];

	int				tex_endian[4];
	int				tex_line_length[4];
	int				tex_bits_per_pixel[4];
}					t_data;

typedef struct s_minilib
{
	void			*mlx;
	void			*win;
	void			*img;
	t_vector		pos;
	t_vector		dir;
	t_vector		plane;
	t_vector		deltadist;
	t_vector		disttoside;
	t_intvector		mappos;
	int				wallheight;
	double			perpendiculardist;
	t_vector		raydir;
}					t_minilib;

typedef struct s_master
{
	int				wrongmap;
	int				c;
	int				f;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			**campus;
	t_minilib		render;
	t_data			img;
	t_keyboard		keyboard;
	t_intvector		wallmappos;
}					t_master;

typedef struct s_texture
{
	int				index;
	int				x;
	int				y;
	double			step;
	double			pos;
	unsigned int	color;
}					t_texture;

// FUNCTIONS
t_map				*ft_read_file(char *filepath);
t_master			*get_master(t_map *map);
int					getcolor(char *str, t_master *master, int type);
void				renderization(t_minilib *render, t_master *master,
						t_data *img);
void				draw_texture(int hitSide, t_intvector *pos, t_data *img,
						t_master *master);
void				clear(t_data *data);
t_minilib			set_cardial(t_master *master);
void				dda(t_master *master, int *hitSide, t_intvector *step,
						t_intvector *wallMapPos);
t_vector			set_disttoside(t_intvector *step, t_vector raydir,
						t_minilib *render, t_intvector mapPos);
t_vector			setdeltadist(t_vector raydir);
void				setwallheight(t_minilib *render, int hitside,
						t_intvector wallmappos, t_intvector step);
void				rotate(t_master *master);
void				move_x(t_master *master);
void				move_y(t_master *master);
int					controls(void *vars);
t_vector			rotate_vector(t_vector v, double angle);
t_vector			get_player_pos(char **campus);

// CHECK MAP
int					check_filename(char *filename);
int					check_components(char *line, t_master *master);
int					have_valid_wall(char **map);
int					ft_find_leak(char **tab);
int					ft_orizontalwall(char **line);
int					check_around(char **map, int x, int y);
int					around_character(char **tab, t_master *master);

// UTILS
int					is_there_something_wrong(t_master *master, t_map *map);
int					ft_countmatriz(char **mat);
int					initializedefault(t_master *master);
int					ft_countlinecampus(t_map *list);
void				ft_replacechar(char *str, char to_find, char to_replace);
int					is_voidline(char *line);
int					ft_countline(char **map);
int					count_var(char **map, char var);
void				show_map(char **map);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
int					printerror(char *str);
void				msg_error_image_not_found(int i, void *mlx, t_data *img);
int					load_textures(void *mlx, t_data *img, t_master *master);
unsigned int		get_color(int hitSide, t_texture *texture, t_data *img);
int					get_texture_index(int hitSide, t_vector rayDir);
int					get_draw_start_position(int lineHeight);
int					get_draw_end_position(int lineHeight);
void				draw_floor(t_intvector *pos, t_data *img, t_master *master);
void				draw_ceiling(int drawStart, t_intvector *pos, t_data *img,
						t_master *master);
int					get_x_coordinate_texture(int index_img, int hitSide,
						t_master *master, t_data *img);
int					wait_hooks(t_master *master);
int					ft_replacestr(char **str, char *to_replace, int *wrong_map);
// HOOKS
int					key_release(int keycode, t_master *master);
int					key_hook(int keycode, t_master *master);
int					key_exit(t_master *master);

// FREEZE
void				ft_free_stack(t_map *map);
void				ft_free_master(t_master *master);
int					ft_freematriz(char **mat);
void				clear(t_data *data);
void				free_textures(t_master *master);
void				free_cardials(t_master *master);

#endif