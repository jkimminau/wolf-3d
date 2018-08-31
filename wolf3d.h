/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 01:01:05 by jkimmina          #+#    #+#             */
/*   Updated: 2018/08/31 02:01:36 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# define WID 1000
# define LEN 800
# define THREADS 8

# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <pthread.h>
# include <stdio.h>
# include "./minilibx/mlx.h"
# include "./libft/libft.h"
# include "./libft/gnl/get_next_line.h"
# include "./libft/printf/ft_printf.h"

typedef struct	s_img
{
	void		*ptr;
	char		*data_addr;
	int			bpp;
	int			line_size;
	int			endian;
}				t_img;

typedef struct	s_map
{
	char		**map;
	char
}				t_map;

typedef struct	s_wolf
{
	void		*mlx;
	void		*win;
	t_img		*img;
	char		**map;
}				t_wolf;

typedef struct	s_thread
{
	pthread_t	tid;
	int		i;
	t_wolf		*wolf;
}		t_thread;

void			free_all(t_wolf *wolf);
t_img			*init_img(void *mlx);
t_wolf			*init_wolf();
int				handle_exit(t_wolf *wolf);
int				handle_keys(int key, t_wolf *wolf);
void			img_pixel_put(t_img *img, int x, int y, int color);
void			*draw(void *thread);
//void			render(t_fdf *fdf);

#endif
