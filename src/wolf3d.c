
#include <wolf3d.h>

/*int		loop_events(t_fdf *fdf)
{
	if (fdf->autorotate)
		fdf->cam->x += 2;
	fdf->cam->x = (fdf->cam->x > 359) ? fdf->cam->x % 360 : fdf->cam->x;
	fdf->cam->x += (fdf->cam->x < 0) ? 360 : 0;
	fdf->cam->y = (fdf->cam->y > 359) ? fdf->cam->y % 360 : fdf->cam->y;
	fdf->cam->y += (fdf->cam->y < 0) ? 360 : 0;
	//fdf->color = (fdf->color > 1536) ? 0 : fdf->color + 1;
	mlx_destroy_image(fdf->mlx, fdf->img->ptr);
	free(fdf->img);
	fdf->img = init_img(fdf->mlx);
	render(fdf);
	return (0);
}*/

int		main(int argc, char **argv)
{
	t_wolf	*wolf;

	(void)argv;
	if (argc != 1)
		ft_printf("usage: ./wolf3d \n");
	wolf = init_wolf();
	/*render(fdf);
	mlx_loop_hook(fdf->mlx, loop_events, fdf);*/
	mlx_hook(wolf->win, 2, 0, handle_keys, wolf);
	mlx_hook(wolf->win, 17, 0, handle_exit, wolf);
	mlx_loop(wolf->mlx);
	return (0);
}
