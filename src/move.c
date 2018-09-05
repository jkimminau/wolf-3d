/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 18:48:13 by jkimmina          #+#    #+#             */
/*   Updated: 2018/09/04 19:18:25 by jkimmina         ###   ########.fr       */
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

/*void	strafe(int d, t_wolf *wolf)
{
	t_vec	*pos;
	t_vec	*dir;

	pos = &wolf->player->pos;
	dir = &wolf->player->dir;
	if (wolf->map->map[(int)pos->y][(int)(pos->x + dir->x * d)] == ' ')
		pos->x += dir->x * 0.25 * d;
	if (wolf->map->map[(int)(pos->y + dir->y * d)][(int)pos->x] == ' ')
		pos->y += dir->y * 0.25 * d;
}*/

void	rotate(int d, t_wolf *wolf)
{	
	t_vec	old;

	old = wolf->player->dir;
	wolf->player->dir.x = old.x * cos(ROT_SPEED * d) - old.y * sin(ROT_SPEED * d);
	wolf->player->dir.y = old.x * sin(ROT_SPEED * d) + old.y * cos(ROT_SPEED * d);
	old = wolf->player->plane;
	wolf->player->plane.x = old.x * cos(ROT_SPEED * d) - old.y * sin(ROT_SPEED * d);
	wolf->player->plane.y = old.x * sin(ROT_SPEED * d) + old.y * cos(ROT_SPEED * d);
}
