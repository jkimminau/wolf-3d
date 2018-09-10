/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 23:02:16 by jkimmina          #+#    #+#             */
/*   Updated: 2018/09/09 20:13:04 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

t_ray			init_ray(t_wolf *wolf, t_vec dir)
{
	t_ray		ray;

	ray.x = (int)wolf->player->pos.x;
	ray.y = (int)wolf->player->pos.y;
	ray.delta.x = fabs(1.0 / dir.x);
	ray.delta.y = fabs(1.0 / dir.y);
	ray.inc.x = (dir.x < 0) ? -1 : 1;
	ray.inc.y = (dir.y < 0) ? -1 : 1;
	ray.len.x = ray.delta.x * ((dir.x < 0) ?
			wolf->player->pos.x - ray.x : 1.0 + ray.x - wolf->player->pos.x);
	ray.len.y = ray.delta.y * ((dir.y < 0) ?
			wolf->player->pos.y - ray.y : 1.0 + ray.y - wolf->player->pos.y);
	return (ray);
}

void			get_text(t_wolf *wolf, t_ray *ray)
{
	ray->text = wolf->text[0];
	if (wolf->map->map[ray->y][ray->x] == 'F')
		ray->text = wolf->text[1];
	if (wolf->map->map[ray->y][ray->x] == 'X')
		ray->text = wolf->text[2];
	if (wolf->map->map[ray->y][ray->x] == 'R')
		ray->text = wolf->text[3];
	if (wolf->map->map[ray->y][ray->x] == 'O')
		ray->text = wolf->text[4];
	if (ft_strchr("01", wolf->map->map[ray->y][ray->x]))
		ray->text = wolf->text[5];
	if (wolf->map->map[ray->y][ray->x] == '2')
		ray->text = wolf->text[6];
}

void			fire(t_wolf *wolf, t_ray *ray, t_vec dir)
{
	while (wolf->map->map[ray->y][ray->x] == ' ')
	{
		ray->side = !(ray->len.x < ray->len.y);
		if (ray->len.x < ray->len.y)
		{
			ray->len.x += ray->delta.x;
			ray->x += ray->inc.x;
		}
		else
		{
			ray->len.y += ray->delta.y;
			ray->y += ray->inc.y;
		}
	}
	get_text(wolf, ray);
	if (!ray->side)
		ray->dist = (ray->x - wolf->player->pos.x
			+ (1 - ray->inc.x) / 2) / dir.x;
	else
		ray->dist = (ray->y - wolf->player->pos.y
			+ (1 - ray->inc.y) / 2) / dir.y;
}

int				get_wall_color(t_wolf *wolf, t_ray ray, t_vec dir, int y)
{
	int			color;
	double		text_x;
	int			text_y;

	text_x = ((ray.side) ? wolf->player->pos.x + ray.dist * dir.x
			: wolf->player->pos.y + ray.dist * dir.y);
	text_x = (int)((text_x - floor(text_x)) * ray.text->wid);
	text_x = (!ray.side && dir.x > 0) ?
			ray.text->wid - text_x - 1 : text_x;
	text_x = (ray.side && dir.y < 0) ?
			ray.text->wid - text_x - 1 : text_x;
	text_y = (int)(((double)y - (WIN_LEN - ray.wall_height) / 2)
			/ ray.wall_height * ray.text->len);
	color = *(int *)(ray.text->data_addr +
			(((int)text_x + text_y * ray.text->wid) * ray.text->bpp));
	if (ray.side)
	{
		color = color - (color % 256) / 2;
		color = color - ((((color >> 8) % 256) / 2) << 8);
		color = color - (((color >> 16) / 2) << 16);
	}
	return (color);
}

void			draw_ray(t_wolf *wolf, t_vec dir, int wx)
{
	t_ray		ray;
	int			y;

	ray = init_ray(wolf, dir);
	fire(wolf, &ray, dir);
	ray.wall_height = WIN_LEN / ray.dist;
	y = (WIN_LEN - ray.wall_height) / 2;
	y = (y < 0) ? 0 : y;
	while (y < WIN_LEN)
	{
		if (y < (ray.wall_height + WIN_LEN) / 2)
			img_pixel_put(wolf->img, wx, y, get_wall_color(wolf, ray, dir, y));
		else
			img_pixel_put(wolf->img, wx, y, 0x777777);
		y++;
	}
}
