/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 01:51:22 by jkimmina          #+#    #+#             */
/*   Updated: 2018/09/04 18:51:22 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void		free_map(t_map *map)
{
	int		i;

	i = 0;
	while (i < map->len)
		free(map->map[i++]);
	free(map->map);
	free(map);
	map = 0;
}

int		init_map(t_wolf *wolf, char *filename)
{
	int		fd;
	char		*line;

	wolf->map->len = 0;
	wolf->map->wid = 0;
	wolf->map->exit.x = -1;
	wolf->map->exit.y = -1;
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
	char		*tmp;

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
	{
		if ((tmp = ft_strstr(l, "S")))
		{
			if (wolf->player)
				return (-1);
			wolf->player = init_player((float)(ft_strstr(l,"S") - l), (float)y);
			*tmp = ' ';
		}
		if (ft_strstr(l, "E"))
		{
			if (wolf->map->exit.x != -1 || wolf->map->exit.y != -1)
				return (-1);
			wolf->map->exit.x = (float)(ft_strstr(l,"S") - l);
			wolf->map->exit.y = (float)y;
		}
		wolf->map->map[y++] = l;
	}
	if (wolf->map->exit.x == -1 || wolf->map->exit.y == -1)
		return (-1);
	if (wolf->player == 0)
		wolf->player = init_player(1.0f, 1.0f);
	close(fd);
	return (1);
}
