/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 01:03:37 by jkimmina          #+#    #+#             */
/*   Updated: 2018/08/31 01:14:44 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void		free_all(t_wolf *wolf)
{
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
	if (!(img->ptr = mlx_new_image(mlx, WID, LEN)))
		return (0);
	img->data_addr = mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line_size, &img->endian);
	img->bpp /= 8;
	return (img);
}

t_wolf		*init_wolf(void)
{
	t_wolf	*wolf;

	if (!(wolf = (t_wolf *)malloc(sizeof(t_wolf))))
		return (0);
	wolf->mlx = mlx_init();
	wolf->win = mlx_new_window(wolf->mlx, WID, LEN, "WOLF-3D");
	wolf->img = init_img(wolf->mlx);
	return (wolf);
}
