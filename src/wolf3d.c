/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 18:36:15 by jkimmina          #+#    #+#             */
/*   Updated: 2018/09/04 19:34:38 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int		main(int ac, char **av)
{
	t_wolf	*wolf;

	if (ac < 2)
	{
		ft_printf("usage: ./wolf3d [map] ..\n");
		exit(EXIT_FAILURE);
	}
	wolf = init_wolf(ac, av);
	if (load_map(av[1], wolf) == -1)
	{
		ft_printf("failed to load map\n");
		exit(EXIT_FAILURE);
	}
	draw(wolf);
	mlx_hook(wolf->win, EVENT_KEY_PRESS, 0, handle_keys, wolf);
	mlx_hook(wolf->win, EVENT_WINDOW_CLOSE, 0, handle_exit, wolf);
	mlx_loop(wolf->mlx);
	return (0);
}
