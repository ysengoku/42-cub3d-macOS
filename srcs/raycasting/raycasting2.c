/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:30:08 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/29 10:11:22 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"

// static void	get_horizontal_distance(t_cub3d *data, t_ray *ray);

// int	ft_raycasting(t_cub3d *data)
// {
// 	int		count;
// 	t_ray	ray;

// 	count = 0;
// 	// init ray struct
// 	ray.angle_rad = (data->player.angle - FOV / 2) * M_PI / 180;
// 	ray.inc_angle = (FOV / WIN_W) * M_PI / 180;
// 	while (count < WIN_W)
// 	{	
// 		ray.x = data->player.pos_x;
// 		ray.y = data->player.pos_y;
// //	/*=== TO CODE ===*/ 
// 		get_horizontal_distance(data, &ray);
// //		Check vertical intersection & calculate the distance from Player's position to the wall
// // 		Get the smallest distance
// //		Calculate wall_height & check which side
// //			-----> start point of wall = WIN_H / 2 - wall height / 2
// //			-----> end point of wall = WIN_H / 2 + wall height / 2
// 	/*=== TEST ===========================================================*/
// 		ray.wall_height = 0;
// 	/*====================================================================*/
// 		draw_ceiling(data, count,  WIN_H / 2 - ray.wall_height / 2, convert_color(data->ceiling));
// //		draw wall (texture)
// 		draw_floor(data, count, WIN_H / 2 + ray.wall_height / 2, convert_color(data->floor));
// 		ray.angle_rad += ray.inc_angle;
// 		count++;
// 	}
// 	return (0);
// }

// static void	get_horizontal_distance(t_cub3d *data, t_ray *ray)
// {
// 	int	test[5][6] = {
// 		{1,1,1,1,1,1},
// 		{1,0,0,1,0,1},
// 		{1,0,1,0,0,1},
// 		{1,1,0,0,0,1},
// 		{1,1,1,1,1,1}};
	
// 	int	hit;

// 	hit = 0;
// 	ray->inc_x = 0; // to calculate 
// 	ray->inc_y = TEXTURE_SIZE;
// 	// --- Check horizontal intersection ---
// 	// Get the first ray position
// 	ray->y = (data->player.pos_y / TEXTURE_SIZE) * TEXTURE_SIZE; // to check 
// 	ray->x = data->player.pos_x + (ray->y - data->player.pos_y) / tan(ray->angle_rad);
// 	while (!hit)
// 	{
// 		if (test[(int)ray->x][(int)ray->y] == 1)
// 			hit = 1;
// 		else
// 		{
// 			ray->x += ray->inc_x;
// 			ray->y += ray->inc_y;
// 		}
// 	}
// 	// --- Calculate the distance --- Pythagoras’s theorem
// 	ray->x_distance = sqrt(pow(ray->x - data->player.pos_x, 2)
// 			+ pow(ray->y - data->player.pos_y, 2));
// }
