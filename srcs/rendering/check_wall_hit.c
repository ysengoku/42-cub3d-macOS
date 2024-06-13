/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall_hit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 08:07:02 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/04 08:20:59 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	next_step(t_ray *ray, int *is_east_or_west);
static int	get_wall_side(t_ray *ray, t_player *player, int is_east_or_west);

void	check_wall_hit(t_cub3d *data, t_ray *ray)
{
	int		is_vertical_side;

	is_vertical_side = 0;
	while (ray->hit == NOTHING)
	{
		if (data->map.map[ray->map_y][ray->map_x] == '1')
			ray->hit = WALL;
		else
			next_step(ray, &is_vertical_side);
	}
	if (is_vertical_side)
		ray->w_dist = ray->sidedist_y - ray->delta_y;
	else
		ray->w_dist = ray->sidedist_x - ray->delta_x;
	if (ray->w_dist < 0.0001)
		ray->w_dist = 0.0001;
	// if (is_vertical_side == 1)
    // 	ray->w_dist = fabs((ray->map_y - data->player.pos_y
	// 		+ (1 - ray->step_y) * 0.5) / ray->dir_y);
	// else
    // 	ray->w_dist = fabs((ray->map_x - data->player.pos_x
	// 		+ (1 - ray->step_x) * 0.5) / ray->dir_x);
	ray->w_side = get_wall_side(ray, &data->player, is_vertical_side);
	ray->wall_height = (int)(WIN_H / ray->w_dist);
}

void	check_door_hit(t_cub3d *data, t_ray *ray)
{
	int		is_vertical_side;

	is_vertical_side = 0;
	while (ray->hit == NOTHING)
	{
		if (data->map.map[ray->map_y][ray->map_x] == '1')
			ray->hit = WALL;
		if (data->map.map[ray->map_y][ray->map_x] == 'D')
			ray->hit = DOOR;
		else
			next_step(ray, &is_vertical_side);
	}
	if (is_vertical_side)
		ray->w_dist = ray->sidedist_y - ray->delta_y;
	else
		ray->w_dist = ray->sidedist_x - ray->delta_x;
	if (ray->w_dist < 0.0001)
		ray->w_dist = 0.0001;
	// if (is_vertical_side == 1)
    // 	ray->w_dist = fabs((ray->map_y - data->player.pos_y
	// 		+ (1 - ray->step_y) * 0.5) / ray->dir_y);
	// else
    // 	ray->w_dist = fabs((ray->map_x - data->player.pos_x
	// 		+ (1 - ray->step_x) * 0.5) / ray->dir_x);
	ray->w_side = get_wall_side(ray, &data->player, is_vertical_side);
	ray->wall_height = (int)(WIN_H / ray->w_dist);
}

static void	next_step(t_ray *ray, int *is_vertical_side)
{
	if (ray->sidedist_x < ray->sidedist_y)
	{
		ray->sidedist_x += ray->delta_x;
		ray->map_x += ray->step_x;
		*is_vertical_side = 0;
	}
	else
	{
		ray->sidedist_y += ray->delta_y;
		ray->map_y += ray->step_y;
		*is_vertical_side = 1;
	}
}

static int	get_wall_side(t_ray *ray, t_player *player, int is_vertical_side)
{
	if (is_vertical_side == 1)
	{
		if (ray->map_y < player->pos_y)
			return (NO);
		return (SO);
	}
	if (ray->map_x < player->pos_x)
		return (WE);
	return (EA);
}
