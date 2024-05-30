/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:06:55 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/30 14:37:27 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	move_north_east(t_cub3d *data)
// {
// 	if (data->map.mapdata[data->player.pos_y - 1][data->player.pos_x + 1] != '1'
// 		&& data->player.pos_x + 1 < data->map.w - 2 && data->player.pos_y > 2)
// 	{
// 		data->player.pos_x += MOVE;
// 		data->player.pos_y -= MOVE;
// 	}
// }

// void	move_north_west(t_cub3d *data)
// {
// 	if (data->map.mapdata[data->player.pos_y - 1][data->player.pos_x - 1] != '1'
// 		&& data->player.pos_x > 2 && data->player.pos_y > 2)
// 	{
// 		data->player.pos_x -= MOVE;
// 		data->player.pos_y -= MOVE;
// 	}
// }

// void	move_south_west(t_cub3d *data)
// {
// 	if (data->map.mapdata[data->player.pos_y - 1][data->player.pos_x + 1] != '1'
// 		&& data->player.pos_x > 2 && data->player.pos_y + 1 < data->map.h - 2)
// 	{
// 		data->player.pos_x -= MOVE;
// 		data->player.pos_y += MOVE;
// 	}
// }

// void	move_south_east(t_cub3d *data)
// {
// 	if (data->map.mapdata[data->player.pos_y - 1][data->player.pos_x + 1] != '1'
// 		&& data->player.pos_x + 1 < data->map.w - 2
// 		&& data->player.pos_y + 1 < data->map.h - 2)
// 	{
// 		data->player.pos_x += MOVE;
// 		data->player.pos_y += MOVE;
// 	}
// }
	
void	move_north_east(t_cub3d *data, int *x, int *y)
{
	// if (data->map.mapdata[*y - 1][*x + 1] != '1'
	// 	&& *x + 1 < data->map.w - 2 && *y > 2)
	(void) data; //////
	if (test[*y - 1][*x + 1] != '1' && *y > 2)
	{
		*x += MOVE;
		*y -= MOVE;
	}
}

void	move_north_west(t_cub3d *data, int *x, int *y)
{
	// if (data->map.mapdata[*y - 1][*x - 1] != '1' && *x > 2 && *y > 2)
	(void) data; //////
	if (test[*y - 1][*x - 1] != '1' && *x > 2 && *y > 2)
	{
		*x -= MOVE;
		*y -= MOVE;
	}
}

void	move_south_west(t_cub3d *data, int *x, int *y)
{
	// if (data->map.mapdata[*y - 1][*x + 1] != '1' 
	// 	&& *x > 2 && *y + 1 < data->map.h - 2)
	(void) data; //////
	if (test[*y - 1][*x + 1] != '1' && *x > 2)
	{
		*x -= MOVE;
		*y += MOVE;
	}
}

void	move_south_east(t_cub3d *data, int *x, int *y)
{
	// if (data->map.mapdata[*y - 1][*x + 1] != '1'
	// 	&& *x + 1 < data->map.w - 2 && *y + 1 < data->map.h - 2)
	(void) data; //////
	if (test[*y - 1][*x + 1] != '1')
	{
		data->player.pos_x += MOVE;
		data->player.pos_y += MOVE;
	}
}