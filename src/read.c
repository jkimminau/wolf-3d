/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 01:51:22 by jkimmina          #+#    #+#             */
/*   Updated: 2018/08/31 02:05:11 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int		init_map(t_wolf *wolf, char *filename)
{
	int		fd;
	char		*line;

	wolf->map->len = 0;
	wolf->map->wid = 0;
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (-1);
	while (get_next_line(fd, &line) > 0)
	{
		if (wolf->map->wid == 0)
			wolf->map->wid = (int)ft_strlen(line);
		if (wolf->map->len > 0 && wolf->map->wid != (int)ft_strlen(line))
			return (-1);
		wolf->map->len++;
		free(line);
	}
	close(fd);
	return (1);
}

int		load_map(char *filename, t_wolf *wolf)
{
	int		y;
	int		fd;
	char		*l;

	if (!(wolf->map = (t_map *)malloc(sizeof(t_map))))
		return (-1);
	if (init_map(wolf, filename) == -1)
		return (-1);
	if (!(wolf->map->map = (char **)malloc(sizeof(char *) * wolf->map->len)))
		return (-1);
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (-1);
	y = 0;
	while (get_next_line(fd, &l) > 0)
		wolf->map->map[y++] = l;
	close(fd);
	return (1);
}
