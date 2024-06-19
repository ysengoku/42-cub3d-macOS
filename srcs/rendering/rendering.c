/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:30:08 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/19 10:27:48 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_camera(t_cub3d *data);

int	display(t_cub3d *data)
{
	int	x;

	x = 0;
	init_camera(data);
	if (BONUS)
	{
		set_treasure_data(data, &data->treasure);
		draw_minimap_zone(data, (data->mmap.totalsize));
		draw_minimap(data);
		animations(data);
	}
	while (x < WIN_W)
	{
		raycasting(data, x, &data->wall[DR_C + data->animation]);
		x++;
	}
	if (BONUS)
		draw_mmap_player_dir(data);
	return (0);
}

static void	init_camera(t_cub3d *data)
{
	double	direction_rad;

	direction_rad = data->player.dir_degree * M_PI / 180;
	data->player.dir.x = cos(direction_rad);
	data->player.dir.y = sin(direction_rad);
	data->player.plane.x = -data->player.dir.y * data->player.plane_length;
	data->player.plane.y = data->player.dir.x * data->player.plane_length;
}
