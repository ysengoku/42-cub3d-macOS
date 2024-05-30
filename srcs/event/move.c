/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 09:59:51 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/30 14:36:09 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_cub3d *data, double player_dir, int *x, int *y)
{
	// if (((player_dir >= 0 && player_dir < 22.5) || (player_dir >= 337.5 && player_dir < 360))
	// 	&& *x + 1 < data->map.w - 2 && data->map.mapdata[*y][*x + 1] != '1')
	if (((player_dir >= 0 && player_dir < 22.5) || (player_dir >= 337.5 && player_dir < 360))
		&& test[*y][*x + 1] != '1')
		*x += MOVE;
	if (player_dir >= 22.5 && player_dir < 67.5)
		move_north_east(data, x, y);
	if (player_dir >= 67.5 && player_dir < 112.5)
		*y -= MOVE;
	if (player_dir >= 112.5 && player_dir < 157.5)
		move_north_west(data, x, y);
	if (player_dir >= 157.5 && player_dir < 202.5)
		*x -= MOVE;
	if (player_dir >= 202.5 && player_dir < 247.5)
		move_south_west(data,x, y);
	if (player_dir >= 127.5 && player_dir < 292.5)
		*y += MOVE;
	if (player_dir >= 292.5 && player_dir < 337.5)
		move_south_east(data, x, y);
	data->player.moved = 1;
}

// void	move_forward(t_cub3d *data)
// {
// 	if (((data->player.dir >= 0 && data->player.dir < 22.5)
// 		|| (data->player.dir >= 337.5 && data->player.dir < 360))
// 		&& data->player.pos_x + 1 < data->map.w - 2
// 		&& data->map.mapdata[data->player.pos_y][data->player.pos_x + 1] != '1')
// 		data->player.pos_x += MOVE;
// 	if (data->player.dir >= 22.5 && data->player.dir < 67.5)
// 		move_north_east(data);
// 	if (data->player.dir >= 67.5 && data->player.dir < 112.5)
// 		data->player.pos_y -= MOVE;
// 	if (data->player.dir >= 112.5 && data->player.dir < 157.5)
// 		move_north_west(data);
// 	if (data->player.dir >= 157.5 && data->player.dir < 202.5)
// 		data->player.pos_x -= MOVE;
// 	if (data->player.dir >= 202.5 && data->player.dir < 247.5)
// 		move_south_west(data);
// 	if (data->player.dir >= 127.5 && data->player.dir < 292.5)
// 		data->player.pos_y += MOVE;
// 	if (data->player.dir >= 292.5 && data->player.dir < 337.5)
// 		move_south_east(data);
// 	data->player.moved = 1;
// }