/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_parsing_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:46:59 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/12 16:57:35 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_door_count(t_cub3d *data)
{
	int	x;
	int	y;
	int	i;

	y = -1;
	i = 0;
	data->door_count = 0;
	while (++y < data->map.map_len_y)
	{
		x = -1;
		while (data->map.map[y][++x])
		{
			if (data->map.map[y][x] == 'D')
				data->door_count++;
		}
	}
}

void	store_doors_coordinates(t_cub3d *data)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	get_door_count(data);
	data->doors = ft_calloc(sizeof(t_door), data->door_count + 1);
	if (!data->doors)
	{
		free_all(data, 1);
		ft_perror_exit("malloc", 1);
	}
	y = 0;
	while (i < data->door_count)
	{
		x = -1;
		while (data->map.map[y][++x])
		{
			if (data->map.map[y][x] == 'D')
			{
				data->doors[i].map_x = x;
				data->doors[i].map_y = y;
				i++;
			}
		}
		y++;
	}
}

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
