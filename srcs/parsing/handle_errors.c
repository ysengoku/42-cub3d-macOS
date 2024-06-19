/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:00:58 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/05 15:45:25 by yusengok         ###   ########.fr       */
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
}

void	exit_parsing(t_map *data_map, char *message)
{
	free_data_map(data_map);
	ft_error_exit(message, EXIT_FAILURE);
}
