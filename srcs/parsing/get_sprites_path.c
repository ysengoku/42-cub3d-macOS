/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprites_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmougel <jmougel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:53:25 by jmougel           #+#    #+#             */
/*   Updated: 2024/06/19 11:52:08 by jmougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_path(char *line)
{
	char	**ar;
	char	*path;
	int		i;

	if (!line)
		return (NULL);
	path = NULL;
	i = 0;
	ar = ft_split(line, ' ');
	if (!ar)
		return (NULL);
	while (ar[i])
		i++;
	if (i != 2)
		return (free_split(ar), NULL);
	path = ft_strdup(ar[1]);
	free_split(ar);
	return (path);
}

static char	*get_sprite_path(char *sprite, t_map *data_map)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (data_map->data_map[i])
	{
		if (ft_strncmp(data_map->data_map[i], sprite, 2) == 0)
		{
			path = get_path(data_map->data_map[i]);
			break ;
		}
		i++;
	}
	return (path);
}

static int	treat_path(t_cub3d *data, char *str)
{
	int	index;

	if (ft_strncmp(str, "NO", 3) == 0)
		index = 0;
	else if (ft_strncmp(str, "SO", 3) == 0)
		index = 1;
	else if (ft_strncmp(str, "WE", 3) == 0)
		index = 2;
	else if (ft_strncmp(str, "EA", 3) == 0)
		index = 3;
	else
		return (EXIT_FAILURE);
	if (data->wall[index].path)
	{
		free_texture_paths(data->wall, 4);
		exit_parsing(&data->map, "Error\nCub3D: multiple data");
		return (EXIT_FAILURE);
	}
	else
		data->wall[index].path = get_sprite_path(str, &data->map);
	return (EXIT_SUCCESS);
}

int	get_sprites_path(t_cub3d *data)
{
	int	i;

	i = 0;
	while (data->map.data_map[i])
	{
		if (ft_strncmp(data->map.data_map[i], "NO ", 3) == 0)
			treat_path(data, "NO");
		else if (ft_strncmp(data->map.data_map[i], "SO ", 3) == 0)
			treat_path(data, "SO");
		else if (ft_strncmp(data->map.data_map[i], "WE ", 3) == 0)
			treat_path(data, "WE");
		else if (ft_strncmp(data->map.data_map[i], "EA ", 3) == 0)
			treat_path(data, "EA");
		i++;
	}
	if (!data->wall[NO].path || !data->wall[SO].path
		|| !data->wall[WE].path || !data->wall[EA].path)
	{
		free_texture_paths(data->wall, 4);
		exit_parsing(&data->map, "Error\nCub3D: invalid sprite");
	}
	if (BONUS)
		get_door_and_treasure_texture_paths(data);
	return (EXIT_SUCCESS);
}
