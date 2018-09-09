/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 18:48:13 by jkimmina          #+#    #+#             */
/*   Updated: 2018/09/09 03:16:08 by jkimmina         ###   ########.fr       */
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

int		check_exit(t_wolf *wolf)
{
	if (sqrt(pow(wolf->player->pos.x - wolf->map->exit.x - 0.5, 2) + pow(wolf->player->pos.y - wolf->map->exit.y - 0.5, 2)) < 1.5)
	{
		mlx_string_put(wolf->mlx, wolf->win, WIN_WID / 2, WIN_LEN / 2, 0xFFFFFF, "Press (X) to continue to the next level");
		return (1);
	}
	return (0);
}

void	next_level(t_wolf *wolf)
{
	int		i;

	i = 0;
	while (i < wolf->map->len)
		free(wolf->map->map[i++]);
	free(wolf->map->map);
	free(wolf->map);
	free(wolf->player);
	wolf->player = 0;
	if (++wolf->current_level == wolf->max_levels)
		exit(EXIT_SUCCESS);
	if (load_map(wolf->levels[wolf->current_level], wolf) == -1)
	{
		ft_printf("failed to load map\n");
		exit(EXIT_FAILURE);
	}
}
