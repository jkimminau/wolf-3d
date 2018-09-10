/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 01:15:23 by jkimmina          #+#    #+#             */
/*   Updated: 2018/09/09 19:28:54 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

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
	render(wolf);
	if (check_exit(wolf) && key == KEY_X)
		next_level(wolf);
	if (check_gen(wolf) && key == KEY_X)
		activate_gen(wolf);
	return (0);
}
