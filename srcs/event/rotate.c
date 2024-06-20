/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 08:43:31 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/20 13:34:35 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_clockwise(t_cub3d *data)
{
	if (data->anim_close == true || data->anim_open == true)
		return ;
	data->player.dir_rad += ROTATE;
	if (data->player.dir_rad >= TWO_PI)
		data->player.dir_rad = 0;
}

void	rotate_counterclockwise(t_cub3d *data)
{
	if (data->anim_close == true || data->anim_open == true)
		return ;
	data->player.dir_rad -= ROTATE;
	if (data->player.dir_rad < 0)
		data->player.dir_rad = TWO_PI - ROTATE;
}
