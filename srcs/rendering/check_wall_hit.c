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

void	check_wall_hit(t_cub3d *data, t_ray *ray, int x)
{
//	int		hit;
	int		is_east_or_west;

	ray->hit = NOTHING;
	is_east_or_west = 0;
	while (ray->hit == NOTHING)
	{
		if (data->map.map[ray->map_y][ray->map_x] == '1')
			ray->hit = WALL;
		else if (data->map.map[ray->map_y][ray->map_x] == 'D')
			ray->hit = DOOR;
		else
			next_step(ray, &is_east_or_west);
	}
	if (is_east_or_west == 1)
		ray->distance = ray->sidedist_y - ray->delta_y;
	else
		ray->distance = ray->sidedist_x - ray->delta_x;
	/*=== Euclidean distance (more accurate but more expensive to calculate) ===*/
	// if (is_east_or_west == 1)
    // 	ray->distance = sqrt(pow(ray->sidedist_y, 2) + pow(ray->delta_y, 2));
	// else
    // 	ray->distance = sqrt(pow(ray->sidedist_x, 2) + pow(ray->delta_x, 2));
	data->wall_zbuffer[x] = ray->distance;
	ray->wall_side = get_wall_side(ray, &data->player, is_east_or_west);
	ray->wall_height = (int)(WIN_H / ray->distance);
}

static void	next_step(t_ray *ray, int *is_east_or_west)
{
	if (ray->sidedist_x < ray->sidedist_y)
	{
		ray->sidedist_x += ray->delta_x;
		ray->map_x += ray->step_x;
		*is_east_or_west = 0;
	}
	else
	{
		ray->sidedist_y += ray->delta_y;
		ray->map_y += ray->step_y;
		*is_east_or_west = 1;
	}
}

static int	get_wall_side(t_ray *ray, t_player *player, int is_east_or_west)
{
	if (ray->hit == DOOR)
		return (DR);
	if (is_east_or_west == 1)
	{
		if (ray->map_y < player->pos_y)
			return (NO);
		return (SO);
	}
	if (ray->map_x < player->pos_x)
		return (WE);
	return (EA);
}
