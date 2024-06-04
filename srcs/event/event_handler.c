/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:42:38 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/03 13:37:43 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int keysym, t_cub3d *data)
{
	if (keysym == XK_Escape)
		close_window(data);
	if (keysym == XK_Right)
		data->key_pressed_right = 1;
	if (keysym == XK_Left)
		data->key_pressed_left = 1;
	if (keysym == XK_w)
		data->key_pressed_w = 1;
	if (keysym == XK_a)
		data->key_pressed_a = 1;
	if (keysym == XK_s)
		data->key_pressed_s = 1;
	if (keysym == XK_d)
		data->key_pressed_d = 1;
	return (0);
}

int	handle_keyrelease(int keysym, t_cub3d *data)
{
	if (keysym == XK_Right)
		data->key_pressed_right = 0;
	if (keysym == XK_Left)
		data->key_pressed_left = 0;
	if (keysym == XK_w)
		data->key_pressed_w = 0;
	if (keysym == XK_a)
		data->key_pressed_a = 0;
	if (keysym == XK_s)
		data->key_pressed_s = 0;
	if (keysym == XK_d)
		data->key_pressed_d = 0;
	return (0);
}

int	handle_closebutton(t_cub3d *data)
{
	close_window(data);
	return (0);
}

// For bonus
int	handle_mousemove(int x, int y, t_cub3d *data)
{
	// to code
	if (BONUS)
	{
		(void)x;
		(void)y;
		(void)data;
	}
	return (0);
}

// int	handle_mouseevents(int mousecode, int x, int y, t_cub3d *data)
// {
// 	(void)y;
// 	(void)x;
// 	if (mousecode == 4) //scroll up
// 		rotate_counterclockwise(data);
// 	if (mousecode == 5) //scroll down
// 		rotate_clockwise(data);
// 	return (0);
// }
