/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:06:55 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/03 11:27:05 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_north_east(t_cub3d *data, int *x, int *y)
{
	if (data->map.map[*y - MOVE][*x + MOVE] != '1')
	{
		*x += MOVE;
		*y -= MOVE;
	}
}

void	move_north_west(t_cub3d *data, int *x, int *y)
{
	if (data->map.map[*y - MOVE][*x - MOVE] != '1')
	{
		*x -= MOVE;
		*y -= MOVE;
	}
}

void	move_south_west(t_cub3d *data, int *x, int *y)
{
	if (data->map.map[*y - MOVE][*x + MOVE] != '1')
	{
		*x -= MOVE;
		*y += MOVE;
	}
}

void	move_south_east(t_cub3d *data, int *x, int *y)
{
	if (data->map.map[*y - MOVE][*x + MOVE] != '1')
	{
		data->player.pos_x += MOVE;
		data->player.pos_y += MOVE;
	}
}
