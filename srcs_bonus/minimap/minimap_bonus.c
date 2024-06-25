/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:08:42 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/17 15:53:19 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_zone(t_cub3d *data, int size)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
			put_pxl_color(&data->mmap.img, x++, y, MMAP_EMPTY);
		y++;
	}
	x = 0;
	y = 0;
	while (x < (size))
		put_pxl_color(&data->mmap.img, x++, y, MMAP_WALL);
	while (y < (size))
		put_pxl_color(&data->mmap.img, x, y++, MMAP_WALL);
	while (x > 0)
		put_pxl_color(&data->mmap.img, x--, y, MMAP_WALL);
	while (y > 0)
		put_pxl_color(&data->mmap.img, x, y--, MMAP_WALL);
}

void	draw_minimap(t_cub3d *data)
{
	int	cam_x;
	int	cam_y;

	cam_x = data->map.pos_x - 4;
	cam_y = data->map.pos_y - 4;
	data->mmap.minimap_x = 1;
	data->mmap.minimap_y = 1;
	while (cam_y < data->map.pos_y + 5)
	{
		while (cam_x < data->map.pos_x + 5)
		{
			draw_scales(data, &cam_x, &cam_y);
			cam_x++;
			data->mmap.minimap_x += MMAP_SCALE + MMAP_BORDER;
		}
		data->mmap.minimap_x = 1;
		data->mmap.minimap_y += MMAP_SCALE + MMAP_BORDER;
		cam_x = data->map.pos_x - 4;
		cam_y++;
	}
	draw_player(data, data->mmap.totalsize * 0.5,
		data->mmap.totalsize * 0.5, 5);
}

void	draw_mmap_player_dir(t_cub3d *data)
{
	t_vector	dir;
	t_vector	p;

	dir.x = (data->mmap.totalsize) * 0.5;
	dir.y = (data->mmap.totalsize) * 0.5;
	p.x = (int)data->player.pos.x + 0.5;
	p.y = (int)data->player.pos.y + 0.5;
	while ((int)dir.x > 0 && (int)dir.y > 0 && (int)dir.x < data->mmap.totalsize
		&& (int)dir.y < data->mmap.totalsize)
	{
		p.x += (data->player.dir.x / (MMAP_BORDER + MMAP_SCALE));
		p.y += (data->player.dir.y / (MMAP_BORDER + MMAP_SCALE));
		if (!data->map.map[(int)floor(p.y)]
			|| !data->map.map[(int)floor(p.y)][(int)floor(p.x)]
			|| data->map.map[(int)floor(p.y)][(int)floor(p.x)] == ' '
			|| data->map.map[(int)floor(p.y)][(int)floor(p.x)] == '1')
			break ;
		put_pxl_color(&data->mmap.img, (int)dir.x, (int)dir.y, MMAP_DIR);
		dir.x += data->player.dir.x;
		dir.y += data->player.dir.y;
	}
}

void	draw_ray_mmap(t_cub3d *data, t_ray *ray)
{
	t_vector	dir;
	t_vector	p;

	dir.x = (data->mmap.totalsize) * 0.5;
	dir.y = (data->mmap.totalsize) * 0.5;
	p.x = (int)data->player.pos.x + 0.5;
	p.y = (int)data->player.pos.y + 0.5;
	while ((int)dir.x > 0 && (int)dir.y > 0 && (int)dir.x < data->mmap.totalsize
		&& (int)dir.y < data->mmap.totalsize)
	{
		p.x += (ray->dir.x / (MMAP_BORDER + MMAP_SCALE));
		p.y += (ray->dir.y / (MMAP_BORDER + MMAP_SCALE));
		if (!data->map.map[(int)floor(p.y)]
			|| !data->map.map[(int)floor(p.y)][(int)floor(p.x)]
			|| data->map.map[(int)floor(p.y)][(int)floor(p.x)] == ' '
			|| data->map.map[(int)floor(p.y)][(int)floor(p.x)] == '1')
			break ;
		put_pxl_color(&data->mmap.img, (int)dir.x, (int)dir.y, MMAP_RAY);
		dir.x += ray->dir.x;
		dir.y += ray->dir.y;
	}
}
