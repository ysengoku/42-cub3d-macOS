/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:36:40 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/17 09:38:25 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_cub3d *data, int xc, int yc, int r)
{
	int	i;
	int	x;
	int	y;

	x = 0;
	while (x <= r)
	{
		y = (int)sqrt(r * r - x * x);
		i = -y;
		while (i <= y)
		{
			put_pxl_color(&data->mmap.img, xc + x, yc + i, MMAP_P);
			put_pxl_color(&data->mmap.img, xc - x, yc + i, MMAP_P);
			i++;
		}
		x++;
	}
}

static void	draw_scale(t_cub3d *data, int color, int size)
{
	int	x;
	int	y;

	x = data->mmap.minimap_x;
	y = data->mmap.minimap_y;
	while (y < data->mmap.minimap_y + size)
	{
		while (x < data->mmap.minimap_x + size)
		{
			put_pxl_color(&data->mmap.img, x, y, color);
			x++;
		}
		x = data->mmap.minimap_x;
		y++;
	}
	draw_mmap_player_dir(data);
}

void	draw_scales(t_cub3d *data, int *cam_x, int *cam_y)
{
	if (*cam_x < 0 || *cam_y < 0)
		draw_scale(data, MMAP_EMPTY, MMAP_SCALE);
	else if (data->map.map[*cam_y] && data->map.map[*cam_y][*cam_x])
	{
		if (data->map.map[*cam_y][*cam_x] == '1')
			draw_scale(data, MMAP_WALL, MMAP_SCALE);
		else if (data->map.map[*cam_y][*cam_x] == '0')
			draw_scale(data, MMAP_FLOOR, MMAP_SCALE);
		else if (data->map.map[*cam_y][*cam_x] == 'P')
			draw_scale(data, MMAP_FLOOR, MMAP_SCALE);
		else if (data->map.map[*cam_y][*cam_x] == 'O'
			|| data->map.map[*cam_y][*cam_x] == 'D')
			draw_scale(data, MMAP_DOOR, MMAP_SCALE);
	}
	else
		draw_scale(data, MMAP_EMPTY, MMAP_SCALE);
}
