/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprite_data_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:45:40 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/10 14:13:32 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_sprite_count(t_cub3d *data)
{
	int	x;
	int	y;
	int	i;

	y = -1;
	i = 0;
	data->sprite_count = 0;
	while (++y < data->map.map_len_y)
	{
		x = -1;
		while (data->map.map[y][++x])
		{
			if (data->map.map[y][x] == '2')
				data->sprite_count++;
		}
	}
}

void	store_sprites(t_cub3d *data)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	get_sprite_count(data);
	data->sprites = ft_calloc(sizeof(t_sprite), data->sprite_count + 1);
	if (!data->sprites)
	{
		free_all(data, 1);
		ft_perror_exit("malloc", 1);
	}
	y = 0;
	while (i < data->sprite_count)
	{
		x = -1;
		while (data->map.map[y][++x])
		{
			if (data->map.map[y][x] == '2')
			{
				data->sprites[i].map_x = (double)x + 0.5;
				data->sprites[i].map_y = (double)y + 0.5;
				i++;
			}
		}
		y++;
	}
}

void	set_relative_position(t_cub3d *data)
{
	int	i;

	i = 0;
	while (i < data->sprite_count)
	{
		data->sprites[i].relative_x = data->sprites[i].map_x - data->player.pos_x;
		data->sprites[i].relative_y = data->sprites[i].map_y - data->player.pos_y;
		i++;
	}
}
