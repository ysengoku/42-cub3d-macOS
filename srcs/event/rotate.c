/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 08:43:31 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/03 10:26:18 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_clockwise(t_cub3d *data)
{
	data->player.dir += ROTATE;
	if (data->player.dir >= 360)
		data->player.dir = 0;
	data->player.moved = 1;
}

void	rotate_counterclockwise(t_cub3d *data)
{
	data->player.dir -= ROTATE;
	if (data->player.dir < 0)
		data->player.dir = 360 - ROTATE;
	data->player.moved = 1;
}
