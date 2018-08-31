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
	if (key == 53)
	{
		free_all(wolf);
		exit(0);
	}
	/*mlx_destroy_image(fdf->mlx, fdf->img->ptr);
	free(fdf->img);
	fdf->img = init_img(fdf->mlx);
	render(fdf);*/
	return (0);
}
