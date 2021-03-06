/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 18:48:13 by jkimmina          #+#    #+#             */
/*   Updated: 2018/09/09 18:43:59 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	move(int d, t_wolf *wolf)
{
	t_vec	*pos;
	t_vec	*dir;

	pos = &wolf->player->pos;
	dir = &wolf->player->dir;
	if (wolf->map->map[(int)pos->y][(int)(pos->x + dir->x * d)] == ' ')
		pos->x += dir->x * 0.25 * d;
	if (wolf->map->map[(int)(pos->y + dir->y * d)][(int)pos->x] == ' ')
		pos->y += dir->y * 0.25 * d;
}

void	strafe(int d, t_wolf *wolf)
{
	t_vec	*pos;
	t_vec	*dir;

	pos = &wolf->player->pos;
	dir = &wolf->player->dir;
	if (wolf->map->map[(int)pos->y][(int)(pos->x + dir->x * d)] == ' ')
		pos->x += dir->x * 0.25 * d;
	if (wolf->map->map[(int)(pos->y + dir->y * d)][(int)pos->x] == ' ')
		pos->y += dir->y * 0.25 * d;
}

void	rotate(int d, t_wolf *wolf)
{
	t_vec	old;

	old = wolf->player->dir;
	wolf->player->dir.x = old.x *
		cos(ROT_SPEED * d) - old.y * sin(ROT_SPEED * d);
	wolf->player->dir.y = old.x *
		sin(ROT_SPEED * d) + old.y * cos(ROT_SPEED * d);
	old = wolf->player->plane;
	wolf->player->plane.x = old.x *
		cos(ROT_SPEED * d) - old.y * sin(ROT_SPEED * d);
	wolf->player->plane.y = old.x *
		sin(ROT_SPEED * d) + old.y * cos(ROT_SPEED * d);
}

void	next_level(t_wolf *wolf)
{
	free_map(wolf->map);
	free(wolf->player);
	wolf->player = 0;
	if (++wolf->current_level == wolf->max_levels)
		exit(EXIT_SUCCESS);
	mlx_clear_window(wolf->mlx, wolf->win);
	mlx_string_put(wolf->mlx, wolf->win, WIN_WID / 2,
			WIN_LEN / 2, 0xFFFFFF, "Loading. . .");
	if (load_map(wolf->levels[wolf->current_level], wolf) == -1)
	{
		ft_printf("failed to load map\n");
		exit(EXIT_FAILURE);
	}
	render(wolf);
}

void	minimap(t_wolf *wolf)
{
	int		y;
	int		x;

	y = 0;
	while (y < wolf->map->len)
	{
		x = 0;
		while (x < wolf->map->wid)
		{
			if (ft_strchr("12", wolf->map->map[y][x]))
				img_pixel_put(wolf->img, x * 7 + 10, y * 7 + 10, 0xEF09E0);
			else if (wolf->map->map[y][x] == 'E')
				img_pixel_put(wolf->img, x * 7 + 10, y * 7 + 10, 0xFF0000);
			else if (wolf->map->map[y][x] != ' ')
				img_pixel_put(wolf->img, x * 7 + 10, y * 7 + 10, 0xFFFFFF);
			x++;
		}
		y++;
	}
	img_pixel_put(wolf->img, wolf->player->pos.x * 7 + 10,
			wolf->player->pos.y * 7 + 10, 0xFF00);
}
