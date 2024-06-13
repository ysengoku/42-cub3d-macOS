/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:14:18 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/12 14:54:35 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_door_texture_paths(t_cub3d *data)
{
	data->wall[DR].path = ft_strdup(DOOR_TEX);
	data->wall[DR1].path = ft_strdup(DOOR_TEX1);
	data->wall[DR2].path = ft_strdup(DOOR_TEX2);
	data->wall[DR3].path = ft_strdup(DOOR_TEX3);
	if (!data->wall[DR].path)
	{
		free_texture_paths(data->wall, 8);
		exit_parsing(&data->map, "Error\nCub3D: malloc failed");
		return (1);
	}
	return (0);
}

void	switch_door_status(t_cub3d *data)
{
	int	target_x;
	int	target_y;

	target_x = (int)data->player.pos_x;
	target_y = (int)data->player.pos_y;
	if (data->player.dir_x > 0)
		target_x += round(data->player.dir_x);
	else if (data->player.dir_x < 0)
		target_x -= round(-data->player.dir_x);
	if (data->player.dir_y > 0)
		target_y += round(data->player.dir_y);
	else if (data->player.dir_y < 0)
		target_y -= round(-data->player.dir_y);
	if (data->map.map[target_y][target_x] == 'D')
	{
		// anim_open_door();
		data->map.map[target_y][target_x] = 'O';
		data->player.moved = 1;
	}
	else if (data->map.map[target_y][target_x] == 'O')
	{
		// anim_close_door();
		data->map.map[target_y][target_x] = 'D';
		data->player.moved = 1;
	}
}
