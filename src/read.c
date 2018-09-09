/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 01:51:22 by jkimmina          #+#    #+#             */
/*   Updated: 2018/09/09 03:22:36 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	free_map(t_map *map)
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
	char	*line;

	wolf->map->len = 0;
	wolf->map->wid = 0;
	wolf->map->exit.x = -1;
	wolf->map->exit.y = -1;
	wolf->map->gen.x = -1;
	wolf->map->gen.y = -1;
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

int		handle_objs(t_wolf *wolf, char *l, int y)
{
	char	*tmp;

	if ((tmp = ft_strstr(l, "S")))
	{
		if (wolf->player)
			return (-1);
		wolf->player =
			init_player((float)(ft_strstr(l, "S") - l), (float)y);
		*tmp = ' ';
	}
	if ((tmp = ft_strstr(l, "E")))
	{
		if (wolf->map->exit.x != -1 || wolf->map->exit.y != -1)
			return (-1);
		wolf->map->exit.x = (float)(ft_strstr(l, "E") - l);
		wolf->map->exit.y = (float)y;
	}
	if ((tmp = ft_strstr(l, "1")))
	{
		if (wolf->map->gen.x != -1 || wolf->map->gen.y != -1)
			return (-1);
		wolf->map->gen.x = (float)(ft_strstr(l, "1") - l);
		wolf->map->gen.y = (float)y;
	}
	return (1);
}

int		load_map(char *filename, t_wolf *wolf)
{
	int		y;
	int		fd;
	char	*l;

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
		if (handle_objs(wolf, l, y) == -1)
			return (-1);
		wolf->map->map[y++] = l;
	}
	if (wolf->map->exit.x == -1 || wolf->map->exit.y == -1)
		return (-1);
	if (wolf->player == 0)
		wolf->player = init_player(1.0f, 1.0f);
	close(fd);
	return (1);
}

int		load_textures(t_wolf *wolf)
{
	if (!(wolf->text[0] = init_xpm_img(wolf->mlx, "./textures/door.xpm")))
		return (0);
	if (!(wolf->text[1] = init_xpm_img(wolf->mlx, "./textures/floor.xpm")))
		return (0);
	if (!(wolf->text[2] = init_xpm_img(wolf->mlx, "./textures/hex.xpm")))
		return (0);
	if (!(wolf->text[3] = init_xpm_img(wolf->mlx, "./textures/rock.xpm")))
		return (0);
	if (!(wolf->text[4] = init_xpm_img(wolf->mlx, "./textures/smooth.xpm")))
		return (0);
	if (!(wolf->text[5] = init_xpm_img(wolf->mlx, "./textures/switch1.xpm")))
		return (0);
	if (!(wolf->text[6] = init_xpm_img(wolf->mlx, "./textures/switch2.xpm")))
		return (0);
	return (1);
}
