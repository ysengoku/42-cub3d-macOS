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

int	keypress(int keysym, t_cub3d *data)
{
	if (keysym == XK_Escape)
		close_window(data);
	if (keysym == XK_Right)
		data->keys.key_pressed_right = 1;
	if (keysym == XK_Left)
		data->keys.key_pressed_left = 1;
	if (keysym == XK_w)
		data->keys.key_pressed_w = 1;
	if (keysym == XK_a)
		data->keys.key_pressed_a = 1;
	if (keysym == XK_s)
		data->keys.key_pressed_s = 1;
	if (keysym == XK_d)
		data->keys.key_pressed_d = 1;
	if (BONUS)
	{
		if (keysym == XK_e)
			action_event(data);
		if (keysym == XK_x && data->keys.key_pressed_x == 0)
			data->keys.key_pressed_x = 1;
		else if (keysym == XK_x && data->keys.key_pressed_x == 1)
			data->keys.key_pressed_x = 0;
	}
	return (0);
}

int	keyrelease(int keysym, t_cub3d *data)
{
	if (keysym == XK_Right)
		data->keys.key_pressed_right = 0;
	if (keysym == XK_Left)
		data->keys.key_pressed_left = 0;
	if (keysym == XK_w)
		data->keys.key_pressed_w = 0;
	if (keysym == XK_a)
		data->keys.key_pressed_a = 0;
	if (keysym == XK_s)
		data->keys.key_pressed_s = 0;
	if (keysym == XK_d)
		data->keys.key_pressed_d = 0;
	return (0);
}

int	closebutton(t_cub3d *data)
{
	close_window(data);
	return (0);
}
