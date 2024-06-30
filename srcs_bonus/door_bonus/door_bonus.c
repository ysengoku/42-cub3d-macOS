/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:14:18 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/24 10:34:19 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_door_and_treasure_texture_paths(t_cub3d *data)
{
	int	i;

	i = 4;
	if (!BONUS)
		return (EXIT_SUCCESS);
	data->wall[DR_C].path = ft_strdup(DOOR_TEX_CLOSE);
	data->wall[DR1].path = ft_strdup(DOOR_TEX1);
	data->wall[DR2].path = ft_strdup(DOOR_TEX2);
	data->wall[DR3].path = ft_strdup(DOOR_TEX3);
	data->wall[DR4].path = ft_strdup(DOOR_TEX4);
	data->wall[DR5].path = ft_strdup(DOOR_TEX5);
	data->wall[DR_O].path = ft_strdup(DOOR_TEX_OPEN);
	data->wall[TR].path = ft_strdup(TREASURE_TEX);
	data->wall[CE].path = ft_strdup(CEILING);
	data->wall[FL].path = ft_strdup(FLOOR);
	while (i < 14)
	{
		if (!data->wall[i].path)
			return (exit_parsing(data, "malloc", true));
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	animation_open(t_cub3d *data)
{
	int	j;

	j = 0;
	if (data->animation == 6)
	{
		while (j < 90000000)
			j++;
		data->animation = 0;
		data->anim_open = false;
		data->map.map[(int)round(data->player.dir.y)
			+ (int)data->player.pos.y][(int)round(data->player.dir.x)
			+ (int)data->player.pos.x] = 'O';
	}
	else
	{
		while (j < 90000000)
			j++;
		data->animation += 1;
	}
}

static void	animation_close(t_cub3d *data)
{
	int	j;

	j = 0;
	if (data->animation == 0)
	{
		while (j < 90000000)
			j++;
		data->anim_close = false;
		data->map.map[(int)round(data->player.dir.y)
			+ (int)data->player.pos.y][(int)round(data->player.dir.x)
			+ (int)data->player.pos.x] = 'D';
	}
	else
	{
		while (j < 90000000)
			j++;
		data->animation -= 1;
	}
}

void	animations(t_cub3d *data)
{
	if (data->anim_open == true && data->anim_close == false)
		animation_open(data);
	else if (data->anim_close == true && data->anim_open == false)
		animation_close(data);
}

void	anim_door(t_cub3d *data, int target_y, int target_x)
{
	if (data->map.map[target_y][target_x] == 'D' && data->anim_close == false)
	{
		data->map.map[(int)round(data->player.dir.y)
			+ (int)data->player.pos.y][(int)round(data->player.dir.x)
			+ (int)data->player.pos.x] = 'd';
		data->anim_open = true;
		data->animation = 0;
	}
	else if (data->map.map[target_y][target_x] == 'O'
		&& data->anim_open == false)
	{
		data->map.map[(int)round(data->player.dir.y)
			+ (int)data->player.pos.y][(int)round(data->player.dir.x)
			+ (int)data->player.pos.x] = 'o';
		data->anim_close = true;
		data->animation = 6;
	}
}
