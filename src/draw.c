
#include <fdf.h>

void			img_pixel_put(t_img *img, int x, int y, int color)
{
	if (x >= 0 && x < WID && y >= 0 && y < LEN)
		*(int *)(img->data_addr + ((x + y * WID) * img->bpp)) = color;
}

void			draw_line(t_fdf *fdf, t_point p1, t_point p2)
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
}

void			*draw(void *thread)
{
	int			i;
	int			j;
	t_fdf			*fdf;

	fdf= ((t_thread*)thread)->fdf;
	i = ((t_thread*)thread)->i;
	while (i < fdf->map->len)
	{
		j = 0;
		while (j < fdf->map->wid)
		{
			if (j < fdf->map->wid - 1)
				draw_line(fdf, project_point(fdf, fdf->map->points[i][j]),
					project_point(fdf, fdf->map->points[i][j + 1]));
			if (i < fdf->map->len - 1)
				draw_line(fdf, project_point(fdf, fdf->map->points[i][j]),
					project_point(fdf, fdf->map->points[i + 1][j]));
			j++;
		}
		i += THREADS;
	}
	return (NULL);
}

void			render(t_fdf *fdf)
{
	t_thread	list[THREADS];
	int			i;

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
}
