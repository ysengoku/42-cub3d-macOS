/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:14:25 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/03 13:34:22 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_cub3d *data)
{
	img_rendering(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.img, 0, 0);
	if (BONUS)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->mmap.img.img, 0, 0);
	if (data->key_pressed_right)
		rotate_clockwise(data);
	if (data->key_pressed_left)
		rotate_counterclockwise(data);
	if (data->key_pressed_w)
		move_forward(data, &data->player, &data->map);
	if (data->key_pressed_a)
		move_left(data, &data->player, &data->map);
	if (data->key_pressed_s)
		move_backward(data, &data->player, &data->map);
	if (data->key_pressed_d)
		move_right(data, &data->player, &data->map);
	return (0);
}
