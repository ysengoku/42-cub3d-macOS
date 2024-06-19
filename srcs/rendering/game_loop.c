/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:14:25 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/17 09:35:48 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_cub3d *data)
{
	display(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.img, 0, 0);
	if (BONUS)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->mmap.img.img, 0, 0);
	if (data->keys.key_pressed_right)
		rotate_clockwise(data);
	if (data->keys.key_pressed_left)
		rotate_counterclockwise(data);
	if (data->keys.key_pressed_w)
		move_forward(data, &data->player, &data->map);
	if (data->keys.key_pressed_a)
		move_left(data, &data->player, &data->map);
	if (data->keys.key_pressed_s)
		move_backward(data, &data->player, &data->map);
	if (data->keys.key_pressed_d)
		move_right(data, &data->player, &data->map);
	return (0);
}
