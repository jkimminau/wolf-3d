/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 18:34:04 by jkimmina          #+#    #+#             */
/*   Updated: 2018/09/05 00:58:01 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define WIN_WID 1000
# define WIN_LEN 800
# define THREADS 8
# define EVENT_KEY_PRESS 2
# define EVENT_WINDOW_CLOSE 17
# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define ROT_SPEED 3 * M_PI / 180

# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <pthread.h>
# include <stdio.h>
# include "./minilibx/mlx.h"
# include "./libft/libft.h"
# include "./libft/gnl/get_next_line.h"
# include "./libft/printf/ft_printf.h"

typedef struct		s_img
{
	void			*ptr;
	char			*data_addr;
	int				bpp;
	int				line_size;
	int				endian;
	int				wid;
	int				len;
}					t_img;

typedef struct		s_vec
{
	double			x;
	double			y;
}					t_vec;

typedef struct		s_ray
{
	int				x;
	int				y;
	int				side;
	t_vec			len;
	t_vec			delta;
	t_vec			inc;
	double			dist;
	int				wall_height;
}					t_ray;

typedef struct		s_map
{
	char			**map;
	int				wid;
	int				len;
	t_vec			exit;
}					t_map;

typedef struct		s_player
{
	t_vec			pos;
	t_vec			dir;
	t_vec			plane;
}					t_player;

typedef struct		s_wolf
{
	void			*mlx;
	void			*win;
	t_img			*img;
	t_img			*text;
	t_map			*map;
	int				current_level;
	int				max_levels;
	char			**levels;
	t_player		*player;
}					t_wolf;

typedef struct		s_thread
{
	pthread_t		tid;
	int				i;
	t_wolf			*wolf;
}					t_thread;

void				free_all(t_wolf *wolf);
t_img				*init_img(void *mlx);
t_player			*init_player(float x, float y);
t_wolf				*init_wolf(int ac, char **av);
void				free_map(t_map *map);
int					init_map(t_wolf *wolf, char *filename);
int					load_map(char *filename, t_wolf *wolf);
void				move(int d, t_wolf *wolf);
void				rotate(int d, t_wolf *wolf);
int					handle_exit(t_wolf *wolf);
int					handle_keys(int key, t_wolf *wolf);
void				img_pixel_put(t_img *img, int x, int y, int color);
void				draw_ray(t_wolf *wolf, t_vec dir, int wx);
void				*draw_thread(void *arg);
void				render(t_wolf *wolf);

#endif
