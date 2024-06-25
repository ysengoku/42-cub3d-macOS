/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:00:58 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/24 14:01:22 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
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

int	exit_parsing(t_cub3d *data, char *message, bool perror_msg)
{
	free_data_map(&data->map);
	if (!BONUS)
		free_texture_paths(data->wall, 4);
	else if (BONUS)
		free_texture_paths(data->wall, 12);
	ft_putstr_fd("Error\nCub3D: ", 2);
	if (perror_msg == false)
		ft_putstr_fd(message, 2);
	else if (perror_msg == true)
		perror(message);
	if (perror_msg == false)
		write(2, "\n", 1);
	return (EXIT_FAILURE);
}
