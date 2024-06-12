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

void	open_door(t_cub3d *data)
{
	int	i;

	i = 0;
	while (i < data->door_count)
	{
		data->map.map[data->doors[i].map_y][data->doors[i].map_x] = 'O';
		i++;
	}
	data->player.moved = 1;
}

void	close_door(t_cub3d *data)
{
	int	i;

	i = 0;
	while (i < data->door_count)
	{
		data->map.map[data->doors[i].map_y][data->doors[i].map_x] = 'D';
		i++;
	}
	data->player.moved = 1;
}
