/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 01:03:37 by jkimmina          #+#    #+#             */
/*   Updated: 2018/09/09 18:43:53 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void		free_all(t_wolf *wolf)
{
	int		i;

	i = 0;
	while (i < 7)
	{
		mlx_destroy_image(wolf->mlx, wolf->text[i]->ptr);
		free(wolf->text[i++]);
	}
	free_map(wolf->map);
	free(wolf->player);
	mlx_destroy_window(wolf->mlx, wolf->win);
	mlx_destroy_image(wolf->mlx, wolf->img->ptr);
	free(wolf->img);
	mlx_del(wolf->mlx);
	free(wolf);
}

t_img		*init_img(void *mlx)
{
	t_img	*img;

	if (!(img = (t_img *)malloc(sizeof(t_img))))
		return (0);
	if (!(img->ptr = mlx_new_image(mlx, WIN_WID, WIN_LEN)))
		return (0);
	img->data_addr = mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line_size, &img->endian);
	img->bpp /= 8;
	return (img);
}

t_img		*init_xpm_img(void *mlx, char *filename)
{
	t_img	*img;

	if (!(img = (t_img *)malloc(sizeof(t_img))))
		return (0);
	if (!(img->ptr = mlx_xpm_file_to_image(mlx,
			filename, &img->wid, &img->len)))
		return (0);
	img->data_addr = mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line_size, &img->endian);
	img->bpp /= 8;
	return (img);
}

t_player	*init_player(float x, float y)
{
	t_player	*p;

	if (!(p = (t_player *)malloc(sizeof(t_player))))
		return (0);
	p->pos.x = x;
	p->pos.y = y;
	p->dir.x = 1;
	p->dir.y = 0;
	p->plane.x = 0;
	p->plane.y = 0.66;
	return (p);
}

t_wolf		*init_wolf(int ac, char **av)
{
	t_wolf	*wolf;

	if (!(wolf = (t_wolf *)malloc(sizeof(t_wolf))))
		return (0);
	if (!(wolf->mlx = mlx_init()))
		return (0);
	if (!(wolf->win = mlx_new_window(wolf->mlx, WIN_WID, WIN_LEN, "WOLF-3D")))
		return (0);
	if (!(wolf->img = init_img(wolf->mlx)))
		return (0);
	if (!load_textures(wolf))
		return (0);
	wolf->player = 0;
	wolf->current_level = 0;
	wolf->max_levels = ac - 1;
	wolf->levels = av + 1;
	return (wolf);
}
