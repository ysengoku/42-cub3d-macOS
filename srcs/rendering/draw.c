/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:57:21 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/04 08:21:19 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double		get_wall_x(t_cub3d *data, t_ray *ray);

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

void	draw_wall(t_cub3d *data, int x, t_ray *r)
{
	t_line	line;
	double	wall_x;

	ft_memset(&line, 0, sizeof(line));
	line.y_start = data->win_half_h - r->wall_height * 0.5 + data->player.pitch;
	if (line.y_start < 0)
		line.y_start = 0;
	line.y_end = data->win_half_h + r->wall_height * 0.5 + data->player.pitch;
	if (line.y_end > WIN_H)
		line.y_end = WIN_H -1;
	line.y = line.y_start;
	wall_x = get_wall_x(data, r);
	if (r->wall_height != 0)
		line.span = (double)data->wall[r->w_side].h / r->wall_height;
	line.tx_x = (int)(wall_x * (double)data->wall[r->w_side].w);
	if (r->wall_height > WIN_H)
    	line.tx_start_y = (r->wall_height - WIN_H) * 0.5;
	while (++line.y < line.y_end)
	{
		line.tx_y = (int)(((double)line.y - (double)line.y_start
			+ line.tx_start_y) * line.span);
		line.color = get_txcolor(&data->wall[r->w_side],
				line.tx_x, line.tx_y);
		put_pxl_color(&data->img, x, line.y, line.color);
	}
}

static double	get_wall_x(t_cub3d *data, t_ray *ray)
{
	double	wall_x;

	if (ray->w_side == EA)
		wall_x = data->wall[EA].w - (data->player.pos_y + ray->w_dist * ray->dir_y);
	else if (ray->w_side == WE)
		wall_x = data->player.pos_y + ray->w_dist * ray->dir_y;
	else if (ray->w_side == SO)
		wall_x = data->wall[SO].w - (data->player.pos_x + ray->w_dist * ray->dir_x);
	else
		wall_x = data->player.pos_x + ray->w_dist * ray->dir_x;
	// if (ray->w_side == WE || ray->w_side == EA)
	// 	wall_x = data->player.pos_y + ray->w_dist * ray->dir_y;
	// else
	// 	wall_x = data->player.pos_x + ray->w_dist * ray->dir_x;
	// if ((ray->w_side == SO && ray->dir_y > 0)
	// 	|| (ray->w_side == WE && ray->dir_x < 0))
		// wall_x = 1 - wall_x;
	if (wall_x != floor(wall_x))
		wall_x -= floor(wall_x);
	else
		wall_x = 1;
	return (wall_x);
}

//===== Bonus ==================================================================
void	draw_door(t_cub3d *data, int x, t_ray *r, t_xpm_img tex)
{
	t_line	line;
	double	wall_x;

	ft_memset(&line, 0, sizeof(line));
	line.y_start = data->win_half_h - r->wall_height * 0.5 + data->player.pitch;
	if (line.y_start < 0)
		line.y_start = 0;
	line.y_end = data->win_half_h + r->wall_height * 0.5 + data->player.pitch;
	if (line.y_end > WIN_H)
		line.y_end = WIN_H -1;
	line.y = line.y_start;
	wall_x = get_wall_x(data, r);
	if (r->wall_height != 0)
		line.span = (double)data->wall[r->w_side].h / r->wall_height;
	line.tx_x = (int)(wall_x * (double)data->wall[r->w_side].w);
	if (r->wall_height > WIN_H)
    	line.tx_start_y = (r->wall_height - WIN_H) * 0.5;
	while (++line.y < line.y_end)
	{
		line.tx_y = (int)(((double)line.y - (double)line.y_start
			+ line.tx_start_y) * line.span);
		line.color = get_txcolor(&tex, line.tx_x, line.tx_y);
		if (line.color && line.color != 0x000000)
			put_pxl_color(&data->img, x, line.y, line.color);
	}
}
//==============================================================================
