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

static unsigned int get_tex_color(t_xpm_img *texture, int x, int y);

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

void	draw_wall(t_cub3d *data, int x, t_ray *ray)
{
	t_line	line;
	double	wall_x;

	line.y_start = WIN_H / 2 - ray->wall_height / 2;
	line.y_end = WIN_H / 2 + ray->wall_height / 2;
	line.y = line.y_start;
	if (ray->wall_side == NO || ray->wall_side == SO)
		wall_x = data->player.pos_y + ray->distance * ray->dir_y;
	else
		wall_x = data->player.pos_x + ray->distance * ray->dir_x;
	wall_x -= floor(wall_x);
	printf("wall_x: %f\n", wall_x);
	if (ray->wall_height != 0)
		line.span = (double)TEX_SIZE / ray->wall_height;
	else
		line.span = 0;
	line.tex_x = (int)(wall_x * (double)TEX_SIZE);
//	printf("line.tex_x: %d\n", line.tex_x);
	line.tex_y = 0;
	while (line.y <= line.y_end)
	{
		line.tex_y = (int)(((double)line.y - (double)line.y_start) * line.span);
		put_pxl_color(&data->img, x, line.y,
			get_tex_color(&data->wall[ray->wall_side], line.tex_x, line.tex_y));
		line.y++;	
	}
}

static unsigned int get_tex_color(t_xpm_img *texture, int x, int y)
{
    char	*pxl;

    pxl = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
//	printf("color: %d\n", *(unsigned int *)pxl);
	return (*(unsigned int *)pxl);
}
