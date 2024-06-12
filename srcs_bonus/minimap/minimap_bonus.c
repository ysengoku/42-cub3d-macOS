/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:08:42 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/12 16:23:34 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_tile_color(t_minimap *mmap, int color);

void	set_minimap(t_cub3d *data)
{
	int			map_x;
	int			map_y;

	map_y = -1;
	data->mmap.minimap_y = 0;
	while (++map_y < data->map.map_len_y)
	{
		map_x = 0;
		data->mmap.minimap_x = 0;
		while (data->map.map[map_y][map_x])
		{
			if (data->map.map[map_y][map_x] == '1')
				draw_tile_color(&data->mmap, MMAP_WALL);
			else if (data->map.map[map_y][map_x] == 'D')
				draw_tile_color(&data->mmap, MMAP_DOOR);
			else if (data->map.map[map_y][map_x] == ' ')
				draw_tile_color(&data->mmap, MMAP_SPACE);
			else
				draw_tile_color(&data->mmap, MMAP_FLOOR);
			map_x++;
		}
		data->mmap.minimap_y += MMAP_SCALE;
	}
}

static void	draw_tile_color(t_minimap *mmap, int color)
{
	int	x;
	int	y;

	y = mmap->minimap_y;
	while (y < mmap->minimap_y + MMAP_SCALE)
	{
		x = mmap->minimap_x;
		while (x < mmap->minimap_x + MMAP_SCALE)
			put_pxl_color(&mmap->img, x++, y, color);
		y++;
	}
	mmap->minimap_x += MMAP_SCALE;
}

void	draw_player(t_cub3d *data)
{
	int	x;
	int	y;
	int	i;
	int	j;

	y = (int)data->player.pos_y * MMAP_SCALE;
	i = 0;
	while (i < MMAP_SCALE)
	{
		j = -1;
		x = (int)data->player.pos_x * MMAP_SCALE;
		while (++j < MMAP_SCALE)
			put_pxl_color(&data->mmap.img, x++, y, MMAP_P);
		i++;
		y++;
	}
	draw_player_dir(data);
}

void	draw_player_dir(t_cub3d *data)
{
	double	dir_x;
	double	dir_y;

	dir_x = (int)data->player.pos_x * MMAP_SCALE + MMAP_SCALE * 0.5 - 1;
	dir_y = (int)data->player.pos_y * MMAP_SCALE + MMAP_SCALE * 0.5 - 1;
	while (data->map.map[(int)(dir_y / MMAP_SCALE)][(int)(dir_x / MMAP_SCALE)] != '1'
		&& data->map.map[(int)(dir_y / MMAP_SCALE)][(int)(dir_x / MMAP_SCALE)] != 'D')
	{
		put_pxl_color(&data->mmap.img, (int)dir_x, (int)dir_y, MMAP_DIR);
		dir_x += data->player.dir_x;
		dir_y += data->player.dir_y;
	}
}

void	draw_ray_mmap(t_cub3d *data, t_ray *ray)
{
	double	dir_x;
	double	dir_y;

	dir_x = (int)data->player.pos_x * MMAP_SCALE + MMAP_SCALE * 0.5 - 1;
	dir_y = (int)data->player.pos_y * MMAP_SCALE + MMAP_SCALE * 0.5 - 1;
	while (data->map.map[(int)(dir_y / MMAP_SCALE)][(int)(dir_x / MMAP_SCALE)] != '1'
		&& data->map.map[(int)(dir_y / MMAP_SCALE)][(int)(dir_x / MMAP_SCALE)] != 'D')
	{
		put_pxl_color(&data->mmap.img, (int)dir_x, (int)dir_y, MMAP_RAY);
		dir_x += ray->dir_x;
		dir_y += ray->dir_y;
	}
}
