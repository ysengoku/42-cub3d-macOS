/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_rendering.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:14:25 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/28 08:57:58 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_cub3d *data)
{
	if (data->win_ptr)
	{	
		ft_raycasting(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.img, 0, 0);
		if (BONUS)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->mmap.img.img, 0, 0);
		if (data->key_pressed_right)
       		rotate_clockwise(data);
    	if (data->key_pressed_left)
        	rotate_counterclockwise(data);
	}
	return (0);
}
