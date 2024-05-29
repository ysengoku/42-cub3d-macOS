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

static void	close_window(t_cub3d *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	// free other things if needed
	exit(1);
}

int	handle_keyevents(int keysym, t_cub3d *data)
{
	if (keysym == ESC)
		close_window(data);
	if (keysym == RIGHT)
		printf("TEST: -->\n"); //TEST
	if (keysym == LEFT)
		printf("TEST: <--\n"); //TEST
	if (keysym == KEY_W)
		data->player.pos_y -= 1; // TEST (to check the direction)
		// Need to add condition to avid getting out of the map
	if (keysym == KEY_A)
		data->player.pos_x -= 1;  // TEST (to check the direction)
		// Need to add condition to avid getting out of the map
	if (keysym == KEY_S)
		data->player.pos_y += 1;  // TEST (to check the direction)
		// Need to add condition to avid getting out of the map
	if (keysym == KEY_D)
		data->player.pos_x += 1;  // TEST (to check the direction)
		// Need to add condition to avid getting out of the map
	return (0);
}

int	handle_closebutton(t_cub3d *data)
{
	close_window(data);
	return (0);
}

// For bonus
int	handle_mouseevents(int mousecode, int x, int y)
{
	(void)x;
	(void)y;
	if (mousecode == 4) //mouse down
		printf("TEST: mouse down\n"); //TEST
	if (mousecode == 5) //mouse up
		printf("TEST: mouse up\n"); //TEST
	return (0);
}
