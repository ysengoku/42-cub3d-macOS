/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:30:08 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/05 16:18:15 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_camera(t_cub3d *data);
static void	set_ray(t_cub3d *data, t_ray *ray, int x);
static void	set_sidedist(t_ray *ray, t_player *player);

int	ft_raycasting(t_cub3d *data)
{
	int		x;
	t_ray	ray;

	x = 0;
	ft_memset(&ray, 0, sizeof(ray));
	if (data->player.moved)
	{
		init_camera(data);
		while (x < WIN_W)
		{
			set_ray(data, &ray, x);
			check_wall_hit(data, &ray);
			draw_ceiling(data, x, WIN_H / 2, data->ceiling_color);
			draw_floor(data, x, WIN_H / 2, data->floor_color);
			draw_wall(data, x, &ray);
			x++;
		}
		if (BONUS)
			set_minimap(data);
		data->player.moved = 0;
	}
	return (0);
}

static void	init_camera(t_cub3d *data)
{
	double	direction_rad;

	direction_rad = data->player.dir * M_PI / 180;
	data->player.dir_x = cos(direction_rad);
	data->player.dir_y = -sin(direction_rad);
	data->player.plane_x = data->player.dir_y * data->player.plane_length;
	data->player.plane_y = data->player.dir_x * data->player.plane_length;
}


static void	set_ray(t_cub3d *data, t_ray *ray, int x)
{
	ray->camera_p = 2 * x / (double)WIN_W - 1;
	ray->dir_x = data->player.dir_x + data->player.plane_x * ray->camera_p;
	ray->dir_y = data->player.dir_y + data->player.plane_y * ray->camera_p;
	ray->map_x = (int)data->player.pos_x;
	ray->map_y = (int)data->player.pos_y;
	ray->delta_x = fabs(1 / ray->dir_x);
	ray->delta_y = fabs(1 / ray->dir_y);
	set_sidedist(ray, &data->player);
}

static void	set_sidedist(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_y;
	}
}
