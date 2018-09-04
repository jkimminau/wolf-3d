
#include <wolf3d.h>
#include <stdio.h>

void			img_pixel_put(t_img *img, int x, int y, int color)
{
	if (x >= 0 && x < WIN_WID && y >= 0 && y < WIN_LEN)
		*(int *)(img->data_addr + ((x + y * WIN_WID) * img->bpp)) = color;
}

/*void			draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	double		d[3];
	double		x;
	double		y;
	double		z;
	double		inc;

	d[0] = (p2.x - p1.x);
	d[1] = (p2.y - p1.y);
	d[2] = (p2.z - p1.z);
	inc = (fabs(d[0]) > fabs(d[1])) ? fabs(d[0]) : fabs(d[1]);
	x = p1.x;
	y = p1.y;
	z = p1.z;
	while (fabs(x - p2.x) >= 1 || fabs(y - p2.y) >= 1)
	{
		img_pixel_put(fdf->img, (int)x, (int)y,
			color_select(fdf->color, z * 60));
		x += (d[0] / inc);
		y += (d[1] / inc);
		z += (d[2] / inc);
	}
}*/

void			draw_ray(t_wolf *wolf, t_vec dir, int wx)
{
	int		x;
	int		y;
	int		side;
	t_vec		len;
	t_vec		delta;
	t_vec		inc;
	double		dist;
	int			wall_height;
	int			line_y;

	x = (int)wolf->player->pos.x;
	y = (int)wolf->player->pos.y;
	delta.x = fabs(1.0 / dir.x);
	delta.y = fabs(1.0 / dir.y);
	inc.x = (dir.x < 0) ? -1 : 1;
	inc.y = (dir.y < 0) ? -1 : 1;
	len.x = delta.x * ((dir.x < 0) ? wolf->player->pos.x - x : 1.0 + x - wolf->player->pos.x);
	len.y = delta.y * ((dir.y < 0) ? wolf->player->pos.y - y : 1.0 + y - wolf->player->pos.y);
	while (wolf->map->map[y][x] != 'X')
	{ 
		if (len.x < len.y)
		{
			len.x += delta.x;
			x += inc.x;
			side = 0;
		}
		else
		{
			len.y += delta.y;
			y += inc.y;
			side = 1;
		}
	}
	if (!side)
		dist = (x - wolf->player->pos.x + (1 - inc.x) / 2) / dir.x;
	else
		dist = (y - wolf->player->pos.y + (1 - inc.y) / 2) / dir.y;
	wall_height = WIN_LEN / dist;
	line_y = (WIN_LEN - wall_height) / 2;
	line_y = (line_y < 0) ? 0 : line_y;
	while (line_y < WIN_LEN)
	{
		if (line_y < (wall_height + WIN_LEN) / 2)
		{
			double	text_x;
			int		text_y;
			
			text_x = ((side) ? x + dist * dir.x : y + dist * dir.y);
			text_x = (int)((text_x - floor(text_x)) * wolf->text->wid);
			text_x = (!side && dir.x > 0) ? wolf->text->wid - text_x - 1 : text_x;
			text_x = (side && dir.y < 0) ? wolf->text->wid - text_x - 1 : text_x;
			text_y = (int)(((double)line_y - (WIN_LEN - wall_height) / 2) / wall_height * wolf->text->len);
			img_pixel_put(wolf->img, wx, line_y, *(int *)(wolf->text->data_addr + (((int)text_x + text_y * wolf->text->wid) * wolf->text->bpp)));
		}
		else
			img_pixel_put(wolf->img, wx, line_y, 0xd86c45);
		line_y++;
	}
}

void			draw(t_wolf *wolf)
{
	int			x;
	double		camera_r;
	t_vec		dir;

	x = 0;
	while (x < WIN_WID)
	{
		camera_r = 2.0 * x / WIN_WID - 1;
		dir.x = wolf->player->dir.x + wolf->player->plane.x * camera_r;
		dir.y = wolf->player->dir.y + wolf->player->plane.y * camera_r;
		draw_ray(wolf, dir, x);
		x++;
	}
	mlx_clear_window(wolf->mlx, wolf->win);
	mlx_put_image_to_window(wolf->mlx, wolf->win, wolf->img->ptr, 0, 0);
}

/*void			render(t_fdf *fdf)
{
	t_thread	list[THREADS];
	int		i;

	i = 0;
	while (i < THREADS)
	{
		list[i].i = i;
		list[i].fdf = fdf;
		pthread_create(&(list[i]).tid, NULL, draw, &list[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
		pthread_join(list[i++].tid, NULL);
	mlx_clear_window(fdf->mlx, fdf->win);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img->ptr, 0, 0);
}*/
