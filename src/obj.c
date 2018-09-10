/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 18:05:33 by jkimmina          #+#    #+#             */
/*   Updated: 2018/09/09 18:43:53 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int		check_exit(t_wolf *wolf)
{
	if (sqrt(pow(wolf->player->pos.x - wolf->map->exit.x - 0.5, 2)
		+ pow(wolf->player->pos.y - wolf->map->exit.y - 0.5, 2)) < 1.5)
	{
		if (wolf->map->map[(int)wolf->map->gen.y][(int)wolf->map->gen.x] == '1')
			mlx_string_put(wolf->mlx, wolf->win,
				WIN_WID / 2, WIN_LEN / 2, 0xFFFFFF,
				"This door has no power");
		else
		{
			mlx_string_put(wolf->mlx, wolf->win,
				WIN_WID / 2, WIN_LEN / 2, 0xFFFFFF,
				"Press (X) to continue to the next level");
			return (1);
		}
	}
	return (0);
}

int		check_gen(t_wolf *wolf)
{
	if (sqrt(pow(wolf->player->pos.x - wolf->map->gen.x - 0.5, 2)
		+ pow(wolf->player->pos.y - wolf->map->gen.y - 0.5, 2)) < 1.5)
	{
		if (wolf->map->map[(int)wolf->map->gen.y][(int)wolf->map->gen.x] == '1')
			mlx_string_put(wolf->mlx, wolf->win,
				WIN_WID / 2, WIN_LEN / 2, 0xFFFFFF, "Press (X) to turn on");
		else
			mlx_string_put(wolf->mlx, wolf->win,
				WIN_WID / 2, WIN_LEN / 2, 0xFFFFFF, "Press (X) to turn off");
		return (1);
	}
	return (0);
}

void	activate_gen(t_wolf *wolf)
{
	int		y;
	char	*c;

	y = 0;
	while (y < wolf->map->len)
	{
		if ((c = ft_strchr(wolf->map->map[y], '1')))
			*c = '2';
		else if ((c = ft_strchr(wolf->map->map[y], '2')))
			*c = '1';
		y++;
	}
	render(wolf);
	check_gen(wolf);
}
