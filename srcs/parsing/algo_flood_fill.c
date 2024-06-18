/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_flood_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:19:54 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/05 16:14:30 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	recursive(t_cub3d *data, char **dup_map, int pos_x, int pos_y)
{
	if (pos_x + 1 < (int)ft_strlen(dup_map[pos_y]) && dup_map[pos_y][pos_x + 1])
		flood_fill(data, dup_map, pos_x + 1, pos_y);
	else
	{
		data->map.check.invalid_map = true;
		return ;
	}
	if (pos_x - 1 >= 0 && dup_map[pos_y][pos_x - 1])
		flood_fill(data, dup_map, pos_x - 1, pos_y);
	else
	{
		data->map.check.invalid_map = true;
		return ;
	}
	if (pos_y + 1 < data->map.map_len_y && dup_map[pos_y + 1]
		&& ((int)ft_strlen(dup_map[pos_y + 1]) >= pos_x))
		flood_fill(data, dup_map, pos_x, pos_y + 1);
	else
	{
		data->map.check.invalid_map = true;
		return ;
	}
	if (pos_y - 1 >= 0 && dup_map[pos_y - 1]
		&& ((int)ft_strlen(dup_map[pos_y - 1]) >= pos_x))
		flood_fill(data, dup_map, pos_x, pos_y - 1);
	else
	{
		data->map.check.invalid_map = true;
		return ;
	}
}

void	flood_fill(t_cub3d *data, char **dup_map, int pos_x, int pos_y)
{
	data->map.check.old_char = '0';
	data->map.check.new_char = 'x';
	if (dup_map[pos_y][pos_x] == '1'
		|| dup_map[pos_y][pos_x] == data->map.check.new_char)
		return ;
	else if (BONUS && dup_map[pos_y][pos_x] == 'D')
		dup_map[pos_y][pos_x] = data->map.check.new_char;
	else if (BONUS && dup_map[pos_y][pos_x] == 'T')
	{
		dup_map[pos_y][pos_x] = data->map.check.new_char;
		data->map.check.catch_treasure = true;
	}
	else if (dup_map[pos_y][pos_x] == data->map.check.old_char)
		dup_map[pos_y][pos_x] = data->map.check.new_char;
	else if (dup_map[pos_y][pos_x] == 'N'
		|| dup_map[pos_y][pos_x] == 'S'
		|| dup_map[pos_y][pos_x] == 'E'
		|| dup_map[pos_y][pos_x] == 'W')
		dup_map[pos_y][pos_x] = data->map.check.new_char;
	else
	{
		data->map.check.invalid_map = true;
		return ;
	}
	recursive(data, dup_map, pos_x, pos_y);
}

int	algo_flood_fill(t_cub3d *data)
{
	char	**dup_map;
	int		pos_x;
	int		pos_y;

	dup_map = data->map.dup_map;
	pos_x = data->map.pos_x;
	pos_y = data->map.pos_y;
	flood_fill(data, data->map.dup_map, pos_x, pos_y);
	if (data->map.check.invalid_map == true)
	{
		if (!BONUS)
			free_texture_paths(data->wall, 4);
		else
			free_texture_paths(data->wall, 12);
		exit_parsing(&data->map, "Error\nCub3D: map not close");
	}
	else if (BONUS && data->map.check.catch_treasure == false)
	{
		free_texture_paths(data->wall, 12);
		exit_parsing(&data->map, "Error\nCub3D: treasure not reached");
	}
	return (EXIT_SUCCESS);
}
