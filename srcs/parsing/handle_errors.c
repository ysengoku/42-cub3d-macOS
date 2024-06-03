/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:00:58 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/03 11:07:52 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map[i]);
	map[i] = NULL;
	free(map);
	map = NULL;
}

void	free_data_map(t_map *data_map)
{
	if (data_map->data_map)
	{
		free_split(data_map->data_map);
		data_map->data_map = NULL;
	}
	if (data_map->dup_map)
	{
		free_split(data_map->dup_map);
		data_map->dup_map = NULL;
	}
	if (data_map->map)
	{
		free_split(data_map->map);
		data_map->map = NULL;
	}
	free(data_map->sprite_no);
	data_map->sprite_no = NULL;
	free(data_map->sprite_so);
	data_map->sprite_so = NULL;
	free(data_map->sprite_we);
	data_map->sprite_we = NULL;
	free(data_map->sprite_ea);
	data_map->sprite_ea = NULL;
}

void	ft_exit_parsing(t_map *data_map, char *message)
{
	free_data_map(data_map);
	ft_error_exit(message, EXIT_FAILURE);
}
