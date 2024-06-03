/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:57:21 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/31 17:02:19 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_cub3d *data, int x, int end, int ceiling_color)
{
	while (end > 0)
		put_pxl_color(&data->img, x, end--, ceiling_color);
}

void	draw_floor(t_cub3d *data, int x, int start, int floor_color)
{
	while (start < WIN_H)
		put_pxl_color(&data->img, x, start++, floor_color);
}

/* Temporary version without texture */
void	draw_wall_tmp(t_cub3d *data, int x, t_ray *ray)
{
	int	start;
	int	end;

	start = WIN_H / 2 - ray->wall_height / 2;
	end = WIN_H / 2 + ray->wall_height / 2;
	while (start <= end)
		put_pxl_color(&data->img, x, start++, data->colors[ray->wall_side]);
}

// void	draw_wall(t_cub3d *data, int x, t_ray *ray)
// {
// 	t_line	line;

// 	line.y_start = WIN_H / 2 - ray->wall_height / 2;
// 	line.y_end = WIN_H / 2 + ray->wall_height / 2;
// 	line.y = line.y_start;
// 	line.span = TEX_SIZE / ray->wall_height; //---> Need to check
// 	line.tex_x = ;
// 	line.tex_y = 0;
// 	while (line.y <= line.y_end)
// 	{
		
// 	}
// }