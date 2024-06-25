/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 08:07:02 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/24 12:56:15 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_door_hit(t_cub3d *data, t_ray *ray, int is_y_axis);
static void	next_step(t_ray *ray, int *is_y_axis);
static void	set_hit_data(t_cub3d *data, t_ray *ray, t_hit *sprite, int y_axis);

void	check_hit(t_cub3d *data, t_ray *ray)
{
	int		is_y_axis;

	is_y_axis = 0;
	while (!ray->wall.hit && !ray->closed_d.hit)
	{
		if (data->map.map[ray->map_y][ray->map_x] == '1')
		{
			set_hit_data(data, ray, &ray->wall, is_y_axis);
			if (ray->nearest_sprite_dist == 0)
				ray->nearest_sprite_dist = ray->wall.dist;
		}
		if (BONUS)
			check_door_hit(data, ray, is_y_axis);
		next_step(ray, &is_y_axis);
	}
}

static void	check_door_hit(t_cub3d *data, t_ray *ray, int is_y_axis)
{
	if (data->map.map[ray->map_y][ray->map_x] == 'D'
		&& !ray->closed_d.hit)
	{
		set_hit_data(data, ray, &ray->closed_d, is_y_axis);
		if (ray->nearest_sprite_dist == 0)
			ray->nearest_sprite_dist = ray->closed_d.dist;
	}
	if (data->map.map[ray->map_y][ray->map_x] == 'O'
		&& !ray->open_d.hit)
		set_hit_data(data, ray, &ray->open_d, is_y_axis);
	if ((data->map.map[ray->map_y][ray->map_x] == 'd'
		|| data->map.map[ray->map_y][ray->map_x] == 'o'))
		set_hit_data(data, ray, &ray->anim_d, is_y_axis);
}

static void	next_step(t_ray *ray, int *is_y_axis)
{
	if (ray->sidedist.x < ray->sidedist.y)
	{
		ray->sidedist.x += ray->delta.x;
		ray->map_x += ray->step_x;
		*is_y_axis = 0;
	}
	else
	{
		ray->sidedist.y += ray->delta.y;
		ray->map_y += ray->step_y;
		*is_y_axis = 1;
	}
}

static void	set_hit_data(t_cub3d *data, t_ray *ray, t_hit *sprite, int y_axis)
{
	sprite->hit = 1;
	if (y_axis)
		sprite->dist = ray->sidedist.y - ray->delta.y;
	else
		sprite->dist = ray->sidedist.x - ray->delta.x;
	if (sprite->dist < 0.00001)
		sprite->dist = 0.00001;
	if (y_axis && ray->map_y < data->player.pos.y)
		sprite->side = SO;
	else if (y_axis && ray->map_y >= data->player.pos.y)
		sprite->side = NO;
	else if (!y_axis && ray->map_x < data->player.pos.x)
		sprite->side = EA;
	else
		sprite->side = WE;
	sprite->h = (int)(WIN_H / sprite->dist);
}
