/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 01:15:23 by jkimmina          #+#    #+#             */
/*   Updated: 2018/09/03 20:34:06 by jkimmina         ###   ########.fr       */
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
	t_vec	old;

	if (key == KEY_ESC)
	{
		free_all(wolf);
		exit(0);
	}
	else if (key == KEY_UP)
	{
		if (wolf->map->map[(int)wolf->player->pos.y][(int)(wolf->player->pos.x + wolf->player->dir.x)] == ' ')
			wolf->player->pos.x += wolf->player->dir.x * 0.25;
		if (wolf->map->map[(int)(wolf->player->pos.y + wolf->player->dir.y)][(int)wolf->player->pos.x] == ' ')
			wolf->player->pos.y += wolf->player->dir.y * 0.25;
	}
	else if (key == KEY_DOWN)
	{
		if (wolf->map->map[(int)wolf->player->pos.y][(int)(wolf->player->pos.x - wolf->player->dir.x)] == ' ')
			wolf->player->pos.x -= wolf->player->dir.x * 0.25;
		if (wolf->map->map[(int)(wolf->player->pos.y - wolf->player->dir.y)][(int)wolf->player->pos.x] == ' ')
			wolf->player->pos.y -= wolf->player->dir.y * 0.25;
	}
	if (key == KEY_RIGHT)
	{
		old = wolf->player->dir;
		wolf->player->dir.x = old.x * cos(ROT_SPEED) - old.y * sin(ROT_SPEED);
		wolf->player->dir.y = old.x * sin(ROT_SPEED) + old.y * cos(ROT_SPEED);
		old = wolf->player->plane;
		wolf->player->plane.x = old.x * cos(ROT_SPEED) - old.y * sin(ROT_SPEED);
		wolf->player->plane.y = old.x * sin(ROT_SPEED) + old.y * cos(ROT_SPEED);
	}
	if (key == KEY_LEFT)
	{
		old = wolf->player->dir;
		wolf->player->dir.x = old.x * cos(-ROT_SPEED) - old.y * sin(-ROT_SPEED);
		wolf->player->dir.y = old.x * sin(-ROT_SPEED) + old.y * cos(-ROT_SPEED);
		old = wolf->player->plane;
		wolf->player->plane.x = old.x * cos(-ROT_SPEED) - old.y * sin(-ROT_SPEED);
		wolf->player->plane.y = old.x * sin(-ROT_SPEED) + old.y * cos(-ROT_SPEED);
	}
	/*if (sqrt(pow(wolf->map->exit.x - wolf->player->pos.x, 2) + pow(wolf->map->exit.y - wolf->player->pos.y, 2)) < 1.0)
	{
		printf("wtf\n");
		wolf->current_level++;
		if (wolf->current_level > wolf->max_levels)
		{
			free_all(wolf);
			exit(0);
		}
		free_map(wolf->map);
		free(wolf->player);
		load_map(wolf->levels[wolf->current_level], wolf);
	}*/
	mlx_destroy_image(wolf->mlx, wolf->img->ptr);
	free(wolf->img);
	wolf->img = init_img(wolf->mlx);
	draw(wolf);
	//if (key == KEY_LEFT)
	//	wolf->player->dir -= 5;
	return (0);
}
