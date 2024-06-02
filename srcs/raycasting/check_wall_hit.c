#include "cub3d.h"

static void	next_step(t_ray *ray, int *is_east_or_west);

void	check_wall_hit(t_cub3d *data, t_ray *ray)
{
	int		hit;
	int		is_east_or_west;
	double	distance;

	hit = 0;
	is_east_or_west = 0;
	while (!hit)
	{
		if (data->map.mapdata[ray->map_y][ray->map_x] == '1')
			hit = 1;
		else
			next_step(ray, &is_east_or_west);
		/*
		{
			if (ray->sidedist_x < ray->sidedist_y)
			{
				ray->sidedist_x += ray->delta_x;
				ray->map_x += ray->step_x;
				is_east_or_west = 0;
			}
			else
			{
				ray->sidedist_y += ray->delta_y;
				ray->map_y += ray->step_y;
				is_east_or_west = 1;
			}
		}
		*/
	}
	if (is_east_or_west == 1)
	{
		distance = ray->sidedist_y - ray->delta_y;
		if (ray->map_y < data->player.pos_y)
			ray->wall_side = NO;
		else
			ray->wall_side = SO;
	}
	else
	{
		distance = ray->sidedist_x - ray->delta_x;
		if (ray->map_x < data->player.pos_x)
			ray->wall_side = WE;
		else
			ray->wall_side = EA;
	}
	ray->wall_height = (int)(WIN_H / distance);
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
