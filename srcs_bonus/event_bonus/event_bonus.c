/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:35:23 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/21 08:38:00 by jmougel          ###   ########.fr       */
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
	data->previous_mouse_x = x;
	return (0);
}

static void	finish_game(t_cub3d *data)
{
	system("afplay ./assets/sound/congrat.wav");
	printf("\033[1m\033[32mCONGRATULATION ! You won !\033[0m\n");
	sleep(1);
	close_window(data);
}

static void	set_open_anim(t_cub3d *data)
{
	data->map.map[(int)round(data->player.dir.y)
		+ (int)data->player.pos.y][(int)round(data->player.dir.x)
		+ (int)data->player.pos.x] = 'd';
	data->anim_open = true;
	data->animation = 0;
}

static void	set_close_anim(t_cub3d *data)
{
	data->map.map[(int)round(data->player.dir.y)
		+ (int)data->player.pos.y][(int)round(data->player.dir.x)
		+ (int)data->player.pos.x] = 'o';
	data->anim_close = true;
	data->animation = 6;
}

void	action_event(t_cub3d *data)
{
	int		target_x;
	int		target_y;

	target_x = (int)data->player.pos.x;
	target_y = (int)data->player.pos.y;
	if (data->player.dir.x > 0)
		target_x += round(data->player.dir.x);
	else if (data->player.dir.x < 0)
		target_x -= round(-data->player.dir.x);
	if (data->player.dir.y > 0)
		target_y += round(data->player.dir.y);
	else if (data->player.dir.y < 0)
		target_y -= round(-data->player.dir.y);
	if (data->map.map[target_y][target_x] == 'D' && data->anim_close == false)
		set_open_anim(data);
	else if (data->map.map[target_y][target_x] == 'O'
		&& data->anim_open == false)
		set_close_anim(data);
	if (data->map.map[target_y][target_x] == 'D'
		|| data->map.map[target_y][target_x] == 'O')
		anim_door(data, target_y, target_x);
	if (BONUS && data->map.map[target_y][target_x] == 'T')
		finish_game(data);
}
