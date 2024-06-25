/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl_iteratif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:26:12 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/24 11:44:35 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	apply_on_pos(char **dup_map, int x, int y)
{
	if (dup_map[y][x] == '0')
		dup_map[y][x] = 'P';
	else if (dup_map[y][x] == '1' || dup_map[y][x] == 'T'
		|| dup_map[y][x] == 'P')
		(void)"skip";
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	find_pos(t_cub3d *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[j])
	{
		while (map[j][i])
		{
			if (map[j][i] == 'P')
			{
				data->map.check.x = i;
				data->map.check.y = j;
				return ;
			}
			i++;
		}
		i = 0;
		j++;
	}
	data->map.check.x = 0;
	data->map.check.y = 0;
	return ;
}

static int	find_treasure(t_cub3d *data, char **dup_map, int x, int y)
{
	if (y - 1 >= 0 && dup_map[y - 1]
		&& ((int)ft_strlen(dup_map[y - 1]) >= x) && dup_map[y - 1][x] == 'T')
		return (EXIT_SUCCESS);
	if (y + 1 < data->map.map_len_y && dup_map[y + 1]
		&& ((int)ft_strlen(dup_map[y + 1]) >= x) && dup_map[y + 1][x] == 'T')
		return (EXIT_SUCCESS);
	if (x - 1 >= 0 && dup_map[y][x - 1] && dup_map[y][x - 1] == 'T')
		return (EXIT_SUCCESS);
	if (x + 1 < (int)ft_strlen(dup_map[y]) && dup_map[y][x + 1]
		&& dup_map[y][x + 1] == 'T')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static int	apply_cross_player(t_cub3d *data, char **dup_map, int x, int y)
{
	dup_map[y][x] = '1';
	if (y - 1 < 0 || !dup_map[y - 1] || ((int)ft_strlen(dup_map[y - 1]) < x)
		|| apply_on_pos(dup_map, x, y - 1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (y + 1 > data->map.map_len_y || !dup_map[y + 1]
		|| ((int)ft_strlen(dup_map[y + 1])) < x
		|| apply_on_pos(dup_map, x, y + 1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (x - 1 < 0 || !dup_map[y][x - 1]
		|| apply_on_pos(dup_map, x - 1, y) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (x + 1 > (int)ft_strlen(dup_map[y]) || !dup_map[y][x + 1]
		|| apply_on_pos(dup_map, x + 1, y) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	flood_fill_iter(t_cub3d *data, char **dup_map)
{
	find_pos(data, dup_map);
	while (data->map.check.x != 0 || data->map.check.y != 0)
	{
		if (BONUS
			&& find_treasure(data, dup_map,
				data->map.check.x, data->map.check.y) == EXIT_SUCCESS)
			data->map.check.catch_treasure = true;
		if (apply_cross_player(data, dup_map,
				data->map.check.x, data->map.check.y) == EXIT_FAILURE)
		{
			data->map.check.invalid_map = true;
			return ;
		}
		find_pos(data, dup_map);
	}
}
