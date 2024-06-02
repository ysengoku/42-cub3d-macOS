/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:42:38 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/23 14:21:12 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	handle_keyevents(int keysym, t_cub3d *data)
{
	if (keysym == ESC)
		close_window(data);
	if (keysym == RIGHT)
		rotate_clockwise(data);
	if (keysym == LEFT)
		rotate_counterclockwise(data);
	if (keysym == KEY_W) //z
		move_forward(data, data->player.dir, &data->player.pos_x,
			&data->player.pos_y);
	if (keysym == KEY_A) //q
		move_left(data, data->player.dir, &data->player.pos_x,
			&data->player.pos_y);
	if (keysym == KEY_S) //s
		move_backward(data, data->player.dir, &data->player.pos_x,
			&data->player.pos_y);
	if (keysym == KEY_D) //d
		move_right(data, data->player.dir, &data->player.pos_x,
			&data->player.pos_y);
	return (0);
}

int	handle_keypress(int keysym, t_cub3d *data)
{
	if (keysym == ESC)
		close_window(data);
	if (keysym == RIGHT)
		data->key_pressed_right = 1;
	if (keysym == LEFT)
		data->key_pressed_left = 1;
	if (keysym == KEY_W) //z
		move_forward(data, data->player.dir, &data->player.pos_x,
			&data->player.pos_y);
	if (keysym == KEY_A) //q
		move_left(data, data->player.dir, &data->player.pos_x,
			&data->player.pos_y);
	if (keysym == KEY_S) //s
		move_backward(data, data->player.dir, &data->player.pos_x,
			&data->player.pos_y);
	if (keysym == KEY_D) //d
		move_right(data, data->player.dir, &data->player.pos_x,
			&data->player.pos_y);
	return (0);
}

int	handle_keyrelease(int keysym, t_cub3d *data)
{
	if (keysym == RIGHT)
		data->key_pressed_right = 0;
	if (keysym == LEFT)
		data->key_pressed_left = 0;
	return (0);
}

/*
int	handle_mouseevents(int mousecode, int x, int y, t_cub3d *data)
{
	(void)x;
	(void)y;
	if (mousecode == 4) //mouse down
		rotate_counterclockwise(data); //TEST
	if (mousecode == 5) //mouse up
		rotate_clockwise(data); //TEST
	return (0);
}
*/

// For bonus
int handle_mousemove(int x, int y, t_cub3d *data)
{
	// to code
	(void)x;
	(void)y;
	(void)data;
	return (0);
}
