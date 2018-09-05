/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 20:12:37 by jkimmina          #+#    #+#             */
/*   Updated: 2018/09/05 00:54:35 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void			img_pixel_put(t_img *img, int x, int y, int color)
{
	if (x >= 0 && x < WIN_WID && y >= 0 && y < WIN_LEN)
		*(int *)(img->data_addr + ((x + y * WIN_WID) * img->bpp)) = color;
}

void			*draw_thread(void *arg)
{
	t_wolf		*wolf;
	int			x;
	double		camera_r;
	t_vec		dir;

	wolf = (t_wolf *)((t_thread *)arg)->wolf;
	x = ((t_thread *)arg)->i;
	while (x < WIN_WID)
	{
		camera_r = 2.0 * x / WIN_WID - 1;
		dir.x = wolf->player->dir.x + wolf->player->plane.x * camera_r;
		dir.y = wolf->player->dir.y + wolf->player->plane.y * camera_r;
		draw_ray(wolf, dir, x);
		x += THREADS;
	}
	return (NULL);
}

void			render(t_wolf *wolf)
{
	t_thread	list[THREADS];
	int			i;

	i = 0;
	while (i < THREADS)
	{
		list[i].i = i;
		list[i].wolf = wolf;
		pthread_create(&(list[i]).tid, NULL, draw_thread, &list[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
		pthread_join(list[i++].tid, NULL);
	mlx_clear_window(wolf->mlx, wolf->win);
	mlx_put_image_to_window(wolf->mlx, wolf->win, wolf->img->ptr, 0, 0);
}
