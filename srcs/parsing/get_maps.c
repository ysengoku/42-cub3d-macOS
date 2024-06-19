/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_maps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:57:09 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/19 11:21:38 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_length(t_map *data_map)
{
	int	i;
	int	j;
	int	map_len_x;

	i = 0;
	j = 0;
	map_len_x = 0;
	while (data_map->dup_map[j])
	{
		while (data_map->dup_map[j][i])
		{
			i++;
		}
		if (map_len_x < i)
			map_len_x = i;
		i = 0;
		j++;
	}
	data_map->map_len_y = j;
	data_map->map_len_x = map_len_x + 1;
	return (EXIT_SUCCESS);
}

static int	get_start_map(char **data_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data_map[i])
	{
		if (data_map[i][0] == ' '
			|| data_map[i][0] == '1'
			|| data_map[i][0] == '0')
		{
			while (data_map[i][j])
			{
				if (data_map[i][j] == '1' || data_map[i][j++] == '0')
					return (i);
			}
		}
		j = 0;
		i++;
	}
	return (-1);
}

static char	**get_map(t_map *data_map)
{
	char	**map;
	int		index_start_map;
	int		i;

	index_start_map = get_start_map(data_map->data_map);
	if (index_start_map == -1)
		return (exit_parsing(data_map, "Error\nCub3D: map not found"), NULL);
	i = index_start_map;
	while (data_map->data_map[i])
		i++;
	map = ft_calloc(i + 1, sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	while (data_map->data_map[index_start_map])
	{
		map[i] = ft_strdup(data_map->data_map[index_start_map++]);
		if (!map)
			return (free_split(map), NULL);
		i++;
	}
	map[i] = NULL;
	return (map);
}

int	get_maps(t_cub3d *data)
{
	data->map.map = get_map(&data->map);
	if (!data->map.map)
		return (exit_parsing(&data->map, "Error\nCub3D"), EXIT_FAILURE);
	data->map.dup_map = get_map(&data->map);
	if (!data->map.dup_map)
		return (exit_parsing(&data->map, "Error\nCub3D"), EXIT_FAILURE);
	get_length(&data->map);
	return (EXIT_SUCCESS);
}
