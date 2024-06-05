/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:59:04 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/05 16:14:52 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check(int *player, int *i, int j, t_map *data_map)
{
	if (data_map->dup_map[j][*i] == 'N'
		|| data_map->dup_map[j][*i] == 'S'
		|| data_map->dup_map[j][*i] == 'E'
		|| data_map->dup_map[j][*i] == 'W')
	{
		data_map->player = data_map->dup_map[j][*i];
		data_map->pos_x = *i;
		data_map->pos_y = j;
		*player += 1;
		*i += 1;
	}
	else if (data_map->dup_map[j][*i] == '1'
		|| data_map->dup_map[j][*i] == '0'
		|| data_map->dup_map[j][*i] == 32)
	{
		*i += 1;
	}
	else
	{
		exit_parsing(data_map, "Error\nCub3D: invalid map");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_valid_char(t_map *data_map)
{
	int		i;
	int		j;
	int		player;

	i = 0;
	j = 0;
	player = 0;
	while (data_map->dup_map[j])
	{
		while (data_map->dup_map[j][i])
			check(&player, &i, j, data_map);
		i = 0;
		j++;
	}
	if (player != 1 || data_map->pos_x == 0 || data_map->pos_y == 0)
		exit_parsing(data_map, "Error\nCub3D: invalid player");
	if (data_map->dup_map[data_map->pos_y][data_map->pos_x] == 'N')
		data_map->p_dir = N;
	else if (data_map->dup_map[data_map->pos_y][data_map->pos_x] == 'S')
		data_map->p_dir = S;
	else if (data_map->dup_map[data_map->pos_y][data_map->pos_x] == 'E')
		data_map->p_dir = E;
	else if (data_map->dup_map[data_map->pos_y][data_map->pos_x] == 'W')
		data_map->p_dir = W;
	return (EXIT_SUCCESS);
}

int	check_map(t_map *data_map)
{
	check_valid_char(data_map);
	algo_flood_fill(data_map);
	return (EXIT_SUCCESS);
}
