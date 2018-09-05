/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 01:15:23 by jkimmina          #+#    #+#             */
/*   Updated: 2018/09/05 00:52:52 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int		loop_events(t_wolf *wolf)
{
	(void)wolf;
	return (0);
}

int		handle_exit(t_wolf *wolf)
{
	free_all(wolf);
	exit(EXIT_SUCCESS);
	return (0);
}

int		handle_keys(int key, t_wolf *wolf)
{
	if (key == KEY_ESC)
		handle_exit(wolf);
	else if (key == KEY_UP || key == KEY_DOWN || key == KEY_W || key == KEY_S)
		move((key == KEY_UP || key == KEY_W) ? 1 : -1, wolf);
	else if (key == KEY_RIGHT || key == KEY_LEFT)
		rotate((key == KEY_RIGHT) ? 1 : -1, wolf);
	if (0)
	{
		wolf->current_level++;
		if (wolf->current_level > wolf->max_levels)
			handle_exit(wolf);
		free_map(wolf->map);
		free(wolf->player);
		load_map(wolf->levels[wolf->current_level], wolf);
	}
	mlx_destroy_image(wolf->mlx, wolf->img->ptr);
	free(wolf->img);
	wolf->img = init_img(wolf->mlx);
	render(wolf);
	return (0);
}
