/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 01:15:23 by jkimmina          #+#    #+#             */
/*   Updated: 2018/08/31 01:44:02 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int		handle_exit(t_wolf *wolf)
{
	free_all(wolf);
	exit(0);
	return (0);
}

int		handle_keys(int key, t_wolf *wolf)
{
	if (key == KEY_ESC)
	{
		free_all(wolf);
		exit(0);
	}
	if (sqrt(pow(wolf->map->exit.x - wolf->player->pos.x, 2) + pow(wolf->map->exit.y - wolf->player->pos.y, 2)) < 1.0)
	{
		wolf->current_level++;
		if (wolf->current_level > wolf->max_levels)
		{
			free_all(wolf);
			exit(0);
		}
		free_map(wolf->map);
		free(wolf->player);
		load_map(wolf->levels[wolf->current_level], wolf);
	}
	//if (key == KEY_LEFT)
	//	wolf->player->dir -= 5;
	//if (key == KEY_RIGHT)
	//	wolf->player->dir += 5;
	/*mlx_destroy_image(fdf->mlx, fdf->img->ptr);
	free(fdf->img);
	fdf->img = init_img(fdf->mlx);
	render(fdf);*/
	return (0);
}
