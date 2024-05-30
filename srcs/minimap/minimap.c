/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:08:42 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/30 17:03:11 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_tile(t_minimap *mmap, int color);
static void	draw_player(t_cub3d *data);
static void	draw_player_dir(t_cub3d *data);

void	set_minimap(t_cub3d *data)
{
	int			map_x;
	int			map_y;

	map_y = 0;
	data->mmap.minimap_y = 0;
	data->mmap.scale = (int)(MMAP_H / data->map.maxh);
	while (map_y < data->map.maxh)
	{
		map_x = 0;
		data->mmap.minimap_x = 0;
		// while (data->map.mapdata[map_y][map_x])
		while (test[map_y][map_x])
		{
			// if (data->map.mapdata[map_y][map_x] == '1')
			if (test[map_y][map_x] == '1')
				draw_tile(&data->mmap, MMAP_WALL);
			else if  (test[map_y][map_x] == ' ')
				draw_tile(&data->mmap, TRANSPARENT); //--> doesn't work
			else
				draw_tile(&data->mmap, MMAP_FLOOR);
			map_x++;
		}
		// while (data->mmap.minimap_x < WIN_W)
		// {
		// 	draw_tile(&data->mmap, TRANSPARENT);
		// 	data->mmap.minimap_x++;
		// }
		map_y++;
		data->mmap.minimap_y += data->mmap.scale;
	}
	draw_player(data);
	draw_player_dir(data);
}

static void	draw_tile(t_minimap *mmap, int color)
{
	int	x;
	int	y;

	y = mmap->minimap_y;
	while (y < mmap->minimap_y + mmap->scale)
	{
		x = mmap->minimap_x;
		while (x < mmap->minimap_x + mmap->scale)
			put_pxl_color(&mmap->img, x++, y, color);
		y++;
	}
	mmap->minimap_x += mmap->scale;
}

static void	draw_player(t_cub3d *data)
{
	int	x;
	int	y;
	int	i;
	int	j;

	y = data->player.pos_y * data->mmap.scale;
	i = 0;
	while (i < data->mmap.scale)
	{
		j = -1;
		x = data->player.pos_x * data->mmap.scale;
		while (++j < data->mmap.scale)
			put_pxl_color(&data->mmap.img, x++, y, MMAP_P);
		i++;
		y++;
	}
}

static void	draw_player_dir(t_cub3d *data)
{
	double	dir_x;
	double	dir_y;
	int		steps;
	double	inc_x;
	double	inc_y;
	
	dir_x = (double)data->player.pos_x + data->player.dir_x * 2 + 1;
	dir_y = (double)data->player.pos_y + data->player.dir_y * 2;
	printf("%f, %f\n", dir_x, dir_y);
	steps = data->mmap.scale - 1;
	if (steps < 2)
		steps = 2;
	inc_x = fabs(data->player.pos_x - dir_x) / steps;
	inc_y = fabs(data->player.pos_y - dir_y) / steps;
	while (steps > 0)
	{
		put_pxl_color(&data->mmap.img, (int)dir_x, (int)dir_y, MMAP_DIR);
		dir_x += inc_x;
		dir_y += inc_y;
		steps--;
	}
}