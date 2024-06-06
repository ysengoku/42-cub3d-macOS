/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:35:23 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/06 16:32:53 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mousemove(int x, int y, t_cub3d *data)
{
	(void) y;
	if (data->previous_mouse_x >= 0)
	{
		if (data->previous_mouse_x > x)
			rotate_counterclockwise(data);
		if (data->previous_mouse_x < x)
			rotate_clockwise(data);
	}
	data->player.moved = 1;
	data->previous_mouse_x = x;
	return (0);
}

int	mousescroll(int event, int x, int y, t_cub3d *data)
{
	(void) x;
	(void) y;
	if (event == MOUSE_DOWN)
		data->player.pitch += PITCH;
	if (event == MOUSE_UP)
		data->player.pitch -= PITCH;
	data->player.moved = 1;
	return (0);
}
